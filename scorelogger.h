#ifndef SCORELOGGER_H
#define SCORELOGGER_H

#include <QObject>
#include <QWidget>

class ScoreLogger
{
public:
    void operator=(const ScoreLogger &) = delete;
    ScoreLogger(ScoreLogger &logger) = delete;

    static ScoreLogger *GetInstance();
    static ScoreLogger *myLogger;

    void writeScore(int winner);

private:
    ScoreLogger();

};

#endif // SCORELOGGER_H
