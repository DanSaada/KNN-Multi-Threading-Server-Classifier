//
// Created by tomer on 1/11/23.
//

#include "ExitCommand.h"

/**
 * Constructor of ExitCommand
 * @param defaultIo Io used
 */
ExitCommand::ExitCommand(DefaultIO* defaultIo): Command(){
    setDescription("8. exit\n");
    setDio(defaultIo);
}

/**
 * This function execute the ExitCommand command which basically exit the program.
 * @param info - a struct holding relevant information for the communication between the commands.
 */
void ExitCommand::execute(Info *info) {

}
