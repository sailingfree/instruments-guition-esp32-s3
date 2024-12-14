/*
Copyright (c) 2024 Peter Martin www.naiadhome.com

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <display.h>
#include <StringStream.h>
#include <sdcard.h>
#include <SdFat.h>
#include <SysInfo.h>

// HTML strings
#include <html/style.html> // Must come before the content files
#include <html/index.html>
#include <html/login.html>

/** year part of FAT directory date field
 * \param[in] fatDate Date in packed dir format.
 *
 * \return Extracted year [1980,2107]
 */
static inline uint16_t FAT_YEAR(uint16_t fatDate) {
    return 1980 + (fatDate >> 9);
}
/** month part of FAT directory date field
 * \param[in] fatDate Date in packed dir format.
 *
 * \return Extracted month [1,12]
 */
static inline uint8_t FAT_MONTH(uint16_t fatDate) {
    return (fatDate >> 5) & 0XF;
}
/** day part of FAT directory date field
 * \param[in] fatDate Date in packed dir format.
 *
 * \return Extracted day [1,31]
 */
static inline uint8_t FAT_DAY(uint16_t fatDate) {
    return fatDate & 0X1F;
}

/** hour part of FAT directory time field
 * \param[in] fatTime Time in packed dir format.
 *
 * \return Extracted hour [0,23]
 */
static inline uint8_t FAT_HOUR(uint16_t fatTime) {
    return fatTime >> 11;
}
/** minute part of FAT directory time field
 * \param[in] fatTime Time in packed dir format.
 *
 * \return Extracted minute [0,59]
 */
static inline uint8_t FAT_MINUTE(uint16_t fatTime) {
  return(fatTime >> 5) & 0X3F;
}
/** second part of FAT directory time field
 * Note second/2 is stored in packed time.
 *
 * \param[in] fatTime Time in packed dir format.
 *
 * \return Extracted second [0,58]
 */
static inline uint8_t FAT_SECOND(uint16_t fatTime) {
  return 2*(fatTime & 0X1F);
}

// The web server
WebServer server(80);


void handleFileUpload() {
    Serial.println("In handle upload");
    HTTPUpload &upload = server.upload();
    if(upload.status == UPLOAD_FILE_START) {
        String filename = upload.filename;
    } else if(upload.status == UPLOAD_FILE_WRITE) {
        Serial.printf("BUF %d %s\n", upload.currentSize, upload.buf);
    }
}

class uriHandler : public RequestHandler {
public:
    uriHandler() {
        Serial.printf("uriHandler registered\n");
    }

    bool canHandle(HTTPMethod requestMethod, String uri) override {
        bool result = false;

        if((requestMethod != HTTP_GET))  {
            return false;
        }
        if(uri.endsWith(".html")) {
            Serial.printf("URI %s end s with .html\n", uri.c_str());
            result = true;
        }
        return result;
    }

    bool handle(WebServer & server, HTTPMethod method, String requestUri) override {
        Serial.printf("URI %s\n", requestUri.c_str());
        const int bsize = 4096;
        char buf[bsize];
        Serial.printf("In handler for %s\n", requestUri.c_str());
        if(!file.open(requestUri.c_str(), O_RDONLY)) {
            server.send(404, "text/html", "No such file");
            return false;
        } else {
            //    server.setContentLength(file.dataLength());
            server.sendHeader("Content-Type", "text/html");
            server.send(200, "text/html", "");
            server.sendHeader("Connection", "close");

            uint32_t count =0;
            int c;
            do {
                c = file.readBytes(buf, bsize);
                server.sendContent(buf, c);
                count += c;
            } while (c);
            file.close();

            //   server.send(200);
            return true;
        }
    }
};

// List the request headers
void listHeaders()
{
    int nheaders = server.headers();
    Serial.printf("There are %d headers\n", nheaders);
    for (int h = 0; h < nheaders; h++)
    {
        String name = server.headerName(h);
        String val = server.header(h);
        Serial.printf("Header %d %s=%s\n", h, name.c_str(), val.c_str());
    }
}

// Web server
void webServerSetup(void) {
    server.begin(80);
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Web server started");
        displayText("Web Server started");

        server.addHandler(new uriHandler());

        // This works for a POST with a content encoding of text/plain though application/json also appears to work
        // The result ends up in a header called plain.
        // The file to write to is on the command line as ?file=filename
        server.on("/", HTTP_POST, []() {
            //const uint16_t blen = 32;
            int datalen = server.clientContentLength();
            Serial.printf("POST...\n");
            Serial.printf("length %d\n", datalen);
            int nargs = server.args();
            Serial.printf("There are %d args\n", nargs);
            String body;
            String filename;
            for(int i = 0; i < nargs; i++) {
                String argname = server.argName(i);
                String arg = server.arg(i);
                Serial.printf("Arg %d => %s = %s\n", i, argname.c_str(), arg.c_str());
                if(argname == "plain") {
                    body = arg;
                }
                if(argname == "file") {
                    filename = arg;
                }
            }
            if(filename == "") {
                server.send(404, "application/octet-stream", "No filename supplied");
            } else {
            Serial.printf("Body: %s\n", body.c_str());
            Serial.printf("Filename %s\n", filename.c_str());
            server.send(200, "text/plain", "");
            file.open(filename.c_str(), O_CREAT | O_WRITE | O_TRUNC);
            file.write(body.c_str(), body.length());
            file.close();
            }
        },
        handleFileUpload
        );

        server.on("/", HTTP_GET, []() {
            listHeaders();
            server.send(200, "text/html", style + 
                                            head_html + 
                                            index_html + 
                                            nav + 
                                            footer_html);
            server.sendHeader("Connection", "close");
            });

        server.on("/system", HTTP_GET, [](){
            listHeaders();
            StringStream net, sys, msgs;
            getNetInfo(net);
            getSysInfo(sys);
            getN2kMsgs(msgs);
            server.sendHeader("Connection", "close");
            server.send(200, "text/html", style + 
                    head_html + 
                    "<h1>System</h1>" +
                    "<pre>" + 
                    net.data + 
                    sys.data + 
                    msgs.data + 
                    "</pre>" + 
                    nav +
                    footer_html);
            });

        // Handle listing the sd card
        server.on("/dir", HTTP_GET, []() {
            listHeaders();
            // Read the directory into a string
            StringStream stream;
            String filelist;
            sd.ls(&stream, "/", 0);
            
            FsFile f = file.openNextFile(O_RDONLY);
            char b[256];
            f.getName(b, 255);
            Serial.printf("File %s\n", b);

            // split the list and add the links
            int next = 0;
            do {
                int start = next;
                next = stream.data.indexOf('\n', next + 1);
                String fname = stream.data.substring(start, next - 1);
                Serial.printf("'%s' %d %d\n", fname.c_str(), start, next);
                file.open(fname.c_str(), O_RDONLY);
                size_t size = file.size();
                uint16_t pdate, ptime;
                file.getModifyDateTime(&pdate, & ptime);
                char buf[64];
                snprintf(buf, 63, "%d-%d-%d %d:%d:%d", 
                    FAT_DAY(pdate), FAT_MONTH(pdate), FAT_YEAR(pdate),
                    FAT_HOUR(ptime), FAT_MINUTE(ptime), FAT_SECOND(ptime));
                file.close();
                filelist += "<tr>";
                filelist += "<td>" + fname + "</td>";
                filelist += "<td><a href='/download?file=" + fname + "'>" + fname + "</a></td>";
                filelist += "<td>";
                filelist +=  size;
                filelist += "</td>";
                filelist += "<td>";
                filelist += buf;
                filelist += "</td>";
                filelist += "</tr>";
                next += 1; // skip newline
            } while(next > 0);

            server.sendHeader("Connection", "close");
            server.send(200, "text/html", style + 
                    head_html + 
                    "<h1>Files</h1>" +
                    "<table>" + 
                    filelist +
                    "</table>" +
                    nav +
                    footer_html);            
        });

        // Handle downloading a logfile
        server.on("/download", HTTP_GET, []() {
            listHeaders();
            // Default logfile is the current one
            String logname("logfile.txt");

            int nargs = server.args();
            Serial.printf("There are %d args\n", nargs);
            for(int i = 0; i < nargs; i++) {
                String argname = server.argName(i);
                String arg = server.arg(i);
                Serial.printf("Arg %d => %s = %s\n", i, argname.c_str(), arg.c_str());
                if(argname == "file") {
                    logname = arg;
                }
            }

            if (!file.open(logname.c_str(), O_RDWR)) {
                errorPrint("Reading logfile\n");
                server.send(404, "application/octet-stream", "No such file");
            }
            else {
                Serial.printf("Downloading logfile %s\n", logname.c_str());
                uint32_t filesize = file.size();
                Serial.printf("Opened... %d bytes\n", filesize);

                char* buf;
                const size_t bsize = 8192U;
                buf = (char*)malloc(bsize);
                if (!buf) {
                    Serial.printf("Cannot allocate %d bytes for download\n", bsize);
                }
                else {
                    server.setContentLength(filesize);
                    server.sendHeader("Content-Type", "application/octet-stream");
                    server.sendHeader("Content-Disposition", "attachment; filename=" + logname);
                    server.send(200, "application/octet-stream", "");
                    
                    ulong start = micros();
                    uint32_t count =0;
                    int c;
                    do {
                        c = file.readBytes(buf, bsize);  
                        //memset(buf,'$', bsize); if(count > 819200) {c = 0;} else {c = bsize;}
                        server.sendContent(buf, c); 
                        count += c;
                    } while (c);
                    ulong now = micros();
                    Serial.printf("Read %d bytes in %ld usecs = %.2f kbytes/sec\n", 
                        count, now - start, (float)count / ((now - start) / 1000.0));
                    file.close();
                    free(buf);
                }
            }

            server.sendHeader("Connection", "close");
            });

        delay(10);
        server.begin();
    }
}

void webServerWork() {
    if (WiFi.status() == WL_CONNECTED) {
        server.handleClient();
    }
}