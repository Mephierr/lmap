#include "cli_presenter.h"
#include "i_model.h"
#include "modelimpl.h"
#include "outputformatter.h"
int main(int argc, char** argv) {
    IModel* model = new ModelImpl();
    OutputFormatter* formatter = new OutputFormatter();
    CliPresenter presenter(model, formatter);
    presenter.exec(argc, argv);
    return 0;
}
