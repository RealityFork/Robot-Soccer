#ifndef BROBOT_INCLUDED_
#define BROBOT_INCLUDED_

class RobotBehaviour
{
public:
	virtual void runAction() {};
	BehaviourType type;
	int which;
	int* pstate;

	void switchTo(int w) { which = w; };
};

#endif