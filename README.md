# Project2

The goal of this homework is to become familiar with concurrent processing in Linux using shared memory. You will implement a license manager that allows a set number of application processes to run. For example, think of an organization that buys five licenses for an application (say, Photoshop). At any given time, only five instances of the application can be executed on the server in this organization. If a sixth person requests a license, the proces is put on hold till one of the five licenses is available. Your job is to create the license manager as well as the application such that only the specified number of instances of the application can run.

runsim n < testing.data

Grading
1. Overall submission: 25 pts. Program compiles and upon reading, seems to be able to solve the assigned problem in the specified manner (shared memory/fork/exec).
2. README: 5 pts. Must address any special things you did, or if you missed anything.
3. Makefile: 5pts. Must use suffix rules or pattern rules. You’ll receive only 2 points for Makefile without those
rules.
4. Command line parsing: 5 pts. Program is able to parse the command line appropriately, assigning defaults as needed; issues help if needed. The configuration file should be properly defined, with the comments.
5. Use of perror: 5pts. Program outputs appropriate error messages, making use of perror(3). Errors follw the specified format.
6. Code readability: 10 pts. The code must be readable, with appropriate comments. Author and date should be identified.
7. Proper fork/exec/wait: 15 pts. Code appropriately performs the fork/exec/wait functions. There are no zombie processes. The number of processes is limited as specified in command line options.
8. Shared memory: 10 pts. Shared memory is properly allocated/deallocated and used to synchronize testsim processes.
9. Signals: 10 pts. Code reacts to signals as specified. When the parent is terminated, all children are terminated as well, and shared memory deallocated.
10. Conformance to specifications: 10pts. Code properly creates the log file; the log file has messages in appropriate format; and appropriate messages are displayed to screen.

References and citings: https://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/shm/example-2.html
