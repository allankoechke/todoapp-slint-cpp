#include "app_window.h"

class TodoController {
public:
    TodoController()
    : ui(AppWindow::create()),
    mTodoModel(std::make_shared<slint::VectorModel<TodoData>>()) 
    {
        // Set the todo model as a shared VectorModel
        ui->set_todo_model(mTodoModel);

        // Handle add task callback
        ui->on_add_task(std::bind(&TodoController::AddTask, this, std::placeholders::_1));

        // Handle removing a todo item
        ui->on_remove_task(std::bind(&TodoController::RemoveTask, this, std::placeholders::_1));
    }

    void run() {
        // Start the event loop
        ui->run();
    }

    bool AddTask(const slint::SharedString& task) {
        // Push a new todo item to the vector
        mTodoModel->push_back(TodoData(false, task));

        return true;
    }

    void RemoveTask(const int& index) {
        // Ensure passed index is less than model row_count
        if(index >= mTodoModel->row_count()) return;

        mTodoModel->erase(index);
    }

private:
    slint::ComponentHandle<AppWindow> ui;

    // Create a shared VectorModel
    std::shared_ptr<slint::VectorModel<TodoData>> mTodoModel;
};

int main(int argc, char **argv)
{
    TodoController app;
    app.run();

    return 0;
}
