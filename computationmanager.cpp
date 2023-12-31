//     ____  __________     ___   ____ ___  _____ //
//    / __ \/ ____/ __ \   |__ \ / __ \__ \|__  / //
//   / /_/ / /   / / / /   __/ // / / /_/ / /_ <  //
//  / ____/ /___/ /_/ /   / __// /_/ / __/___/ /  //
// /_/    \____/\____/   /____/\____/____/____/   //
// Auteurs : Prénom Nom, Prénom Nom


// A vous de remplir les méthodes, vous pouvez ajouter des attributs ou méthodes pour vous aider
// déclarez les dans ComputationManager.h et définissez les méthodes ici.
// Certaines fonctions ci-dessous ont déjà un peu de code, il est à remplacer, il est là temporairement
// afin de faire attendre les threads appelants et aussi afin que le code compile.

#include "computationmanager.h"


ComputationManager::ComputationManager(int maxQueueSize): MAX_TOLERATED_QUEUE_SIZE(maxQueueSize)
{
    // TODO
    requestsWaiting = std::vector<Request>();
    computationTypes = std::vector<ComputationType>();
}

int ComputationManager::requestComputation(Computation c) {
    // TODO
    monitorIn();
    requestsWaiting.push_back(Request(c, nextId++));
    computationTypes.push_back(c.computationType);
    int res = nextId-1;
    for(int i = nbGetWorkWaiting; i > 0; --i)
        signal(newRequest);
    monitorOut();
    return res;
}

void ComputationManager::abortComputation(int id) {
    // TODO
}

Result ComputationManager::getNextResult() {
    // TODO
    // Replace all of the code below by your code

    // Filled with some code in order to make the thread in the UI wait
    monitorIn();
    //auto c = Condition();
    //wait(c);
    monitorOut();

    return Result(-1, 0.0);
}

Request ComputationManager::getWork(ComputationType computationType) {
    // TODO
    // Replace all of the code below by your code

    // Filled with arbitrary code in order to make the callers wait
    monitorIn();
    Request r;
    bool isFound = false;
    for(int i = 0; i < requestsWaiting.size(); i++){
        if(computationTypes.at(i) == computationType) {
            r = requestsWaiting.at(i);
            requestsWaiting.erase(requestsWaiting.begin() + i);
            computationTypes.erase(computationTypes.begin() + i);
            isFound = true;
            break;
        }
    }

    while(!isFound) {
        ++nbGetWorkWaiting;
        wait(newRequest);
        --nbGetWorkWaiting;

        if(computationTypes.at(computationTypes.size()) != computationType) {
            r = requestsWaiting.at(requestsWaiting.size());
            requestsWaiting.pop_back();
            computationTypes.pop_back();
            isFound = true;
        }
    }

    monitorOut();

    return r;
}

bool ComputationManager::continueWork(int id) {
    // TODO
    return true;
}

void ComputationManager::provideResult(Result result) {
    // TODO
}

void ComputationManager::stop() {
    // TODO
}
