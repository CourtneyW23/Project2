
typedef struct license{
	time_t time;
	char *shm;
} license;

	int getlicense(void);
	int returnlicense(void);
	int initlicense(void);
	int addtolicenses(int n);
	int removelicenses(int n);
	int logmsg(const char * msg);


