simple Create
{
    parameters:
		string mode;
		int forkNumber = default(0);
		volatile double intervalTime @unit(s) = default(0);
    gates:
        input in[];
        output out[];
}