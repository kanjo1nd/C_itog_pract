#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Obstacle {
public:
    virtual ~Obstacle() = default;
    virtual void overcome() const = 0;
};

class RunningTrack : public Obstacle {
    int length;
public:
    RunningTrack(int len) : length(len) {}
    void overcome() const override {
        cout << "Runs the length of the treadmill " << length << " meters." << endl;
    }
    int getLength() const {
        return length;
    }
};

class Wall : public Obstacle {
    int height;
public:
    Wall(int h) : height(h) {}
    void overcome() const override {
        cout << "Jumps over the wall in height " << height << " meters." << endl;
    }
    int getHeight() const {
        return height;
    }
};

class Participant {
protected:
    string name;
    int maxRun;
    int maxJump;
    bool active;
public:
    Participant(string n, int runDist, int jumpHeight) : name(n), maxRun(runDist), maxJump(jumpHeight), active(true) {}
    virtual void run() = 0;
    virtual void jump() = 0;
    bool isActive() const {
        return active;
    }
    void disqualify() {
        active = false;
    }
    virtual void overcomeObstacle(const Obstacle& obstacle) = 0;
	virtual ~Participant() {}
};

class Robot : public Participant {
public:
    Robot(string n, int runDist, int jumpHeight) : Participant(n, runDist, jumpHeight) {}

    void overcomeObstacle(const Obstacle& obstacle) override {
        if (!isActive()) {
            return;
        }

        const RunningTrack* track = dynamic_cast<const RunningTrack*>(&obstacle);
        const Wall* wall = dynamic_cast<const Wall*>(&obstacle);

        if (track) {
            if (track->getLength() <= maxRun) {
                cout << "Participant [" << name << "] completed the obstacle [Treadmill] on the distance [" << track->getLength() << "]." << endl;
            }
            else {
                cout << "Participant [" << name << "] did not complete the obstacle [Treadmill] on the distance [" << track->getLength() << "]. Passed [" << maxRun << "]." << endl;
                disqualify();
            }
        }
        else if (wall) {
            if (wall->getHeight() <= maxJump) {
                cout << "Participant [" << name << "] passed the obstacle [Wall] at height [" << wall->getHeight() << "]." << endl;
            }
            else {
                cout << "Participant [" << name << "] did not pass the obstacle [Wall] at height [" << wall->getHeight() << "]. Passed [" << maxJump << "]." << endl;
                disqualify();
            }
        }
    }

    void run() override {
        cout << "The robot is running" << endl;
    }

    void jump() override {
        cout << "The robot is jumping" << endl;
    }
};

class Cat : public Participant {
public:
    Cat(string n, int runDist, int jumpHeight) : Participant(n, runDist, jumpHeight) {}

    void overcomeObstacle(const Obstacle& obstacle) override {
        if (!isActive()) {
            return;
        }

        const RunningTrack* track = dynamic_cast<const RunningTrack*>(&obstacle);
        const Wall* wall = dynamic_cast<const Wall*>(&obstacle);

        if (track) {
            if (track->getLength() <= maxRun) {
                cout << "Participant [" << name << "] completed the obstacle [Treadmill] on the distance [" << track->getLength() << "]." << endl;
            }
            else {
                cout << "Participant [" << name << "] did not complete the obstacle [Treadmill] on the distance [" << track->getLength() << "]. Passed [" << maxRun << "]." << endl;
                disqualify();
            }
        }
        else if (wall) {
            if (wall->getHeight() <= maxJump) {
                cout << "Participant [" << name << "] passed the obstacle [Wall] at height [" << wall->getHeight() << "]." << endl;
            }
            else {
                cout << "Participant [" << name << "] did not pass the obstacle [Wall] at height [" << wall->getHeight() << "]. Passed [" << maxJump << "]." << endl;
                disqualify();
            }
        }
    }

    void run() override {
        cout << "The cat is running" << endl;
    }

    void jump() override {
        cout << "The cat is jumping" << endl;
    }
};

class Human : public Participant {
public:
    Human(string n, int runDist, int jumpHeight) : Participant(n, runDist, jumpHeight) {}

    void overcomeObstacle(const Obstacle& obstacle) override {
        if (!isActive()) {
            return;
        }

        const RunningTrack* track = dynamic_cast<const RunningTrack*>(&obstacle);
        const Wall* wall = dynamic_cast<const Wall*>(&obstacle);

        if (track) {
            if (track->getLength() <= maxRun) {
                cout << "Participant [" << name << "] completed the obstacle [Treadmill] on the distance [" << track->getLength() << "]." << endl;
            }
            else {
                cout << "Participant [" << name << "] did not complete the obstacle [Treadmill] on the distance [" << track->getLength() << "]. Passed [" << maxRun << "]." << endl;
                disqualify();
            }
        }
        else if (wall) {
            if (wall->getHeight() <= maxJump) {
                cout << "Participant [" << name << "] passed the obstacle [Wall] at height [" << wall->getHeight() << "]." << endl;
            }
            else {
                cout << "Participant [" << name << "] did not pass the obstacle [Wall] at height [" << wall->getHeight() << "]. Passed [" << maxJump << "]." << endl;
                disqualify();
            }
        }
    }

    void run() override {
        cout << "The man is running" << endl;
    }

    void jump() override {
        cout << "Man jumping" << endl;
    }
};

int main() {
    Human human("Stepa", 500, 2);
    Cat cat("Dog", 300, 3);
    Robot robot("DebD2", 1000, 1);

    RunningTrack track(400);
    Wall wall(2);

    Participant* participants[] = { &human, &cat, &robot };

    Obstacle* obstacles[] = { &track, &wall };

    for (auto participant : participants) {
        for (auto obstacle : obstacles) {
            if (participant->isActive()) {
                participant->overcomeObstacle(*obstacle);
            }
        }
    }
}