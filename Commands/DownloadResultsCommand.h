//
// Created by tomer on 1/11/23.
//

#ifndef KNN_SERVER_DOWNLOADRESULTSCOMMAND_H
#define KNN_SERVER_DOWNLOADRESULTSCOMMAND_H

#include "Command.h"
class DownloadResultsCommand : public Command{
private:
public:
    void execute(Info* info) override;
};


#endif //KNN_SERVER_DOWNLOADRESULTSCOMMAND_H
