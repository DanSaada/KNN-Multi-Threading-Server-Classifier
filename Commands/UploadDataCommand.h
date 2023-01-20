//
// Created by dansa97 on 1/11/23.
//

#ifndef KNN_SERVER_UPLOADDATACOMMAND_H
#define KNN_SERVER_UPLOADDATACOMMAND_H

#include "Command.h"

class UploadDataCommand : public Command{
private:
public:
    explicit UploadDataCommand(DefaultIO* defaultIo): Command() {
        setDescription("1. upload an unclassified csv data file\n");
        setDio(defaultIo);
}
    void execute(Info* info) override;

    void CatalogTrainMaker(Info* info, const string& toSplitString);

    void CatalogTestMaker(Info* info, const string& toSplitString);

    //~UploadDataCommand() override = default;
};




#endif //KNN_SERVER_UPLOADDATACOMMAND_H
