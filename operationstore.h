#ifndef OPERATIONSTORE_H
#define OPERATIONSTORE_H


class OperationStore
{
public:
    OperationStore();
    ~OperationStore();
    int getOpCode();
    void setOpCode(int);

private:
    int opCode;
};



#endif // OPERATIONSTORE_H
