# Philosophers
One of the 42 Wolfsburg core projects.
It represents the Dining Philosopher's problem which is a problem about
sharing recources and synchronization.

# Information:
- Deadlock


What is deadlock?
--------------------------------------------------------------------------------
A deadlock is a situation in which to computer programs that share
the same recource are preventing each other from accesing the recource
which prevents both of them from functioning.

Example #
- Program 1 requests resource A and receives it.
- Program 2 requests resource B and receives it.
- Program 1 requests resource B and is queued up, pending the release of B.
- Program 2 requests resource A and is queued up, pending the release of A.

Neither program can proceed until the other program releases a resource. The operating system cannot know what to do. The only option is to abort (stop) one of the programs.

History-
---------

The earliest computer systems used to run only one program at the time. Due
to this all of the recources of the sytem were available to this one specific
program. Later, sytems started to run multiple programs at once. Therefore,
programs were required to specify recources they need so they could avoid conflicts with other programs running at the same time. Program could request
reservation of recources after they started running. This led to an issue called
deadlock.
Learning to deal with deadlocks had a major impact on the development of operating systems and the structure of databases. Data was structured and the order of requests was constrained in order to avoid creating deadlocks.

--------------------------------------------------------------------------------

