typedef struct {
    uint32_t    year;
    uint16_t    start_month;
    uint16_t    start_day;
    uint16_t    end_month;
    uint16_t    end_day;
} BSTDates;

// Given a date return 1 if the date is BST, 0 otherwise
int utcToGmt(int hour, int year, int month, int day);

// Return true if the current time is BST
bool isBST();
