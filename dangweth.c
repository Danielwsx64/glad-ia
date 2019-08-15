// Actions:
// 1 - move to the target

// Purposes:
// 1 - Hunt an enemy

struct ActionSet_s{
  int targetX;
  int targetY;
  int action;
  int purpose;
  int priority;
} ActionSet_default = {0, 0, 0, 0, 0};

typedef struct ActionSet_s ActionSet;

ActionSet old_glad_action;

// ==== Function prototypes ==============
int huntMove(ActionSet *glad_action);
void performAction(ActionSet glad_action);
void purposeHunting(ActionSet *glad_action);
void actionMove(ActionSet *glad_action);
void defineTarget(ActionSet *glad_action, int x, int y);
void definePriority(ActionSet *glad_action, int priority);
// =======================================


loop(){

  ActionSet glad_action;

  huntMove(&glad_action);

  performAction(glad_action);
}

int huntMove(ActionSet *glad_action){
  int x, y;
  char mensagem[3];

  if(getCloseEnemy()){
    speak("I can see you!");

    /* defineTarget(glad_action, getTargetX(), getTargetY()); */

    return 1;
  }else{
    speak("I'm looking for someone!");

    x = rand() % 25;
    y = rand() % 25;

    defineTarget(glad_action, x, y);
  }

  purposeHunting(glad_action);
  actionMove(glad_action);
  definePriority(glad_action, 0);

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


// Purposes deinition
void purposeHunting(ActionSet *glad_action){
  glad_action->purpose = 1;
}

//Actions definition
void actionMove(ActionSet *glad_action){
  glad_action->action = 1;
}

// Helper functions

void defineTarget(ActionSet *glad_action, int x, int y){
  glad_action->targetX = x;
  glad_action->targetY = y;
}

void definePriority(ActionSet *glad_action, int priority){
  glad_action->priority = priority;
}

int maxHP(){
  return 100 + (10 * getSTR());
}

float lifePercent(){
  return (getHp() / maxHP()) * 100;
}
