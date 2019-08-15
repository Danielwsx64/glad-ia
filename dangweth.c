int howManyEnemies();
void speak(char *);
int rand();
int moveTo(int x, int y);
int getSTR();
int getHp();
int getX();
int getY();
int isSafeThere (float x, float y);
float getSafeRadius();

#define CENTER_POSITION 12

#define NO_ACTION 0
#define MOVE_ACTION 1

#define NO_PURPOSE 0
#define HUNT_PURPOSE 1

#define NO_PRIORITY 0
#define LOW_PRIORITY 1
#define MEDIUM_PRIORITY 2
#define HIGH_PRIORITY 3

struct ActionSet_s{
  int targetX;
  int targetY;
  int action;
  int purpose;
  int priority;
} ActionSet_default = {0, 0, NO_ACTION, NO_PURPOSE, 0};

typedef struct ActionSet_s ActionSet;

ActionSet old_glad_action;


// ==== Function prototypes ==============
int huntMove(ActionSet *glad_action);
void performAction(ActionSet glad_action);
void definePurpose(ActionSet *glad_action, int purpose);
void defineAction(ActionSet *glad_action, int action);
void defineTarget(ActionSet *glad_action, int x, int y);
void definePriority(ActionSet *glad_action, int priority);
int lastTargetX();
int lastTargetY();
int lastPurpose();
int targetSafe(int x, int y);

int makeTargetSafe(int point);

int loop(){

  ActionSet glad_action;

  huntMove(&glad_action);

  performAction(glad_action);

  return 0;
}

int huntMove(ActionSet *glad_action){
  int targetX, targetY;

  if(howManyEnemies()){
    speak("I can see you!");
    return 1;
  }

  speak("I'm looking for someone!");

  if(lastPurpose() == HUNT_PURPOSE && lastTargetX() != getX() && lastTargetY() != getY()){
    targetX = lastTargetX();
    targetY = lastTargetY();
  }else{
    targetX = ( rand() % 23 ) + 1;
    targetY = ( rand() % 23 ) + 1;
  }

  while(!targetSafe(targetX, targetY)){
    targetX = makeTargetSafe(targetX);
    targetY = makeTargetSafe(targetY);
  }

  defineTarget(glad_action, targetX, targetY);
  definePurpose(glad_action, HUNT_PURPOSE);
  defineAction(glad_action, MOVE_ACTION);
  definePriority(glad_action, NO_PRIORITY);

  return 0;
}

void performAction(ActionSet glad_action){

  switch(glad_action.action){
    case 1: // MoveTo

      moveTo(glad_action.targetX, glad_action.targetY);
      break;

    default:
      break;
  }

  old_glad_action = glad_action;
}

void definePurpose(ActionSet *glad_action, int purpose){
  glad_action->purpose = purpose;
}

void defineAction(ActionSet *glad_action, int action){
  glad_action->action = action;
}

void defineTarget(ActionSet *glad_action, int x, int y){
  glad_action->targetX = x;
  glad_action->targetY = y;
}

void definePriority(ActionSet *glad_action, int priority){
  glad_action->priority = priority;
}

int lastPurpose(){
  return old_glad_action.purpose;
}

int lastTargetX(){
  return old_glad_action.targetX;
}

int lastTargetY(){
  return old_glad_action.targetY;
}

int targetSafe(int x, int y){
  if(x < 1 || y < 1 || x > 24 || y > 24){
    return 0;
  }

  if(getSafeRadius() < 3){
    return 1;
  }

  return isSafeThere(x, y);
}

int makeTargetSafe(int point){
  if(point > CENTER_POSITION) {
    return point -1;
  }

  return point + 1;
}

int maxHP(){
  return 100 + (10 * getSTR());
}

float lifePercent(){
  return (getHp() / maxHP()) * 100;
}
