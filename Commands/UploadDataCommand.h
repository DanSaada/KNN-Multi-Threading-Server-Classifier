//
// Created by dansa97 on 1/11/23.
//

#ifndef KNN_SERVER_UPLOADDATACOMMAND_H
#define KNN_SERVER_UPLOADDATACOMMAND_H

#include "Command.h"

class UploadDataCommand : public Command{
private:
public:
    explicit UploadDataCommand(DefaultIO* defaultIo);

    void execute(Info* info) override;

    void CatalogTrainMaker(Info* info, const string& toSplitString);

    void CatalogTestMaker(Info* info, const string& toSplitString);

};




#endif //KNN_SERVER_UPLOADDATACOMMAND_H
