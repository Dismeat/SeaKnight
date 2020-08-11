#include "scorelogger.h"

#include "QFile"
#include "QTextStream"

ScoreLogger *ScoreLogger::myLogger = nullptr;

ScoreLogger::ScoreLogger() {}

void ScoreLogger::writeScore(int winner) {
    QFile file("score.txt");
    if(file.open(QIODevice::WriteOnly |  QIODevice::Append | QIODevice::Text)) {
          QTextStream stream(&file);
          QString score;
          score = ((winner == 0) ? "win 1 player" : "win 2 player");
          stream << score << Qt::endl;
          file.close();
      }
}

ScoreLogger *ScoreLogger::GetInstance() {
    if (myLogger == nullptr) {
        myLogger = new ScoreLogger();
    }
    return myLogger;
}

