simple Create
{
    parameters:
        volatile int forkNumber = default(0);
        volatile double intervalTime @unit(s) = default(0);
    gates:
        output out[];
}