/**
 * @author hockeyhurd
 * @version 2019-05-08
 */

#include "other_fields.h"

FieldPipe::FieldPipe() : Field("-pipe") {

}

b32 FieldPipe::apply(const std::string &args, IFlags &flags) {
    if (args == "-pipe") {
        flags.flags.emplace_back(args);

        return True;
    }

    return False;
}
