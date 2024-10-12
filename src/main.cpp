#include "app-window.h"

int main(int argc, char **argv)
{
    // Create & Instantiate AppWindow
    auto ui = AppWindow::create();

    // Create a shared VectorModel
    auto model = std::make_shared<slint::VectorModel<TodoData>>();

    // Set the todo model as a shared VectorModel
    ui->set_todo_model(model);

    // Handle add task callback
    ui->on_add_task([&](const slint::SharedString& task) -> bool {
        std::cout << "Todo: " << task << std::endl;

        // Push a new todo item to the vector
        model->push_back(TodoData(false, task));

        return true;
    });

    // Handle removing a todo item
    ui->on_remove_task([&](const int& index){
        if(index >= model->row_count()) return;

        model->erase(index);
    });

    // Start event loop
    ui->run();

    return 0;
}
