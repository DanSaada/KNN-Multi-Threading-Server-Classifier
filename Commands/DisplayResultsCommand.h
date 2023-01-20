//
// Created by tomer on 1/11/23.
//

#ifndef KNN_SERVER_DISPLAYRESULTSCOMMAND_H
#define KNN_SERVER_DISPLAYRESULTSCOMMAND_H

#include "Command.h"
class DisplayResultsCommand : public Command{
private:
public:
    explicit DisplayResultsCommand(DefaultIO* defaultIo): Command(){
        setDescription("4. display results");
        setDio(defaultIo);
}
    void execute(Info* info) override;
};


#endif //KNN_SERVER_DISPLAYRESULTSCOMMAND_H
