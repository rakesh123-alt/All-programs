import java.io.*;
import java.util.*;

// Task class to encapsulate task details
class Task {
    private String title;
    private String description;
    private boolean isCompleted;

    public Task(String title, String description) {
        this.title = title;
        this.description = description;
        this.isCompleted = false;
    }

    public String getTitle() {
        return title;
    }

    public String getDescription() {
        return description;
    }

    public boolean isCompleted() {
        return isCompleted;
    }

    public void markAsCompleted() {
        this.isCompleted = true;
    }

    @Override
    public String toString() {
        return "Task: " + title + "\nDescription: " + description + "\nCompleted: " + (isCompleted ? "Yes" : "No") + "\n";
    }
}

// Main application class
public class TaskManager {
    private static final String FILE_NAME = "tasks.txt";
    private List<Task> tasks;

    public TaskManager() {
        tasks = new ArrayList<>();
        loadTasksFromFile();
    }

    public void addTask(String title, String description) {
        tasks.add(new Task(title, description));
        System.out.println("Task added successfully.");
    }

    public void viewTasks() {
        if (tasks.isEmpty()) {
            System.out.println("No tasks available.");
            return;
        }

        for (int i = 0; i < tasks.size(); i++) {
            System.out.println("Task ID: " + (i + 1));
            System.out.println(tasks.get(i));
        }
    }

    public void markTaskAsCompleted(int taskId) {
        if (taskId <= 0 || taskId > tasks.size()) {
            System.out.println("Invalid Task ID.");
            return;
        }

        Task task = tasks.get(taskId - 1);
        task.markAsCompleted();
        System.out.println("Task marked as completed.");
    }

    public void saveTasksToFile() {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(FILE_NAME))) {
            for (Task task : tasks) {
                writer.write(task.getTitle() + "|" + task.getDescription() + "|" + task.isCompleted());
                writer.newLine();
            }
        } catch (IOException e) {
            System.out.println("Error saving tasks: " + e.getMessage());
        }
    }

    public void loadTasksFromFile() {
        File file = new File(FILE_NAME);
        if (!file.exists()) return;

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split("\\|");
                if (parts.length == 3) {
                    Task task = new Task(parts[0], parts[1]);
                    if (Boolean.parseBoolean(parts[2])) {
                        task.markAsCompleted();
                    }
                    tasks.add(task);
                }
            }
        } catch (IOException e) {
            System.out.println("Error loading tasks: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        TaskManager manager = new TaskManager();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\nTask Manager");
            System.out.println("1. Add Task");
            System.out.println("2. View Tasks");
            System.out.println("3. Mark Task as Completed");
            System.out.println("4. Exit");
            System.out.print("Choose an option: ");

            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    System.out.print("Enter task title: ");
                    String title = scanner.nextLine();
                    System.out.print("Enter task description: ");
                    String description = scanner.nextLine();
                    manager.addTask(title, description);
                    break;
                case 2:
                    manager.viewTasks();
                    break;
                case 3:
                    System.out.print("Enter Task ID to mark as completed: ");
                    int taskId = scanner.nextInt();
                    manager.markTaskAsCompleted(taskId);
                    break;
                case 4:
                    manager.saveTasksToFile();
                    System.out.println("Goodbye!");
                    scanner.close();
                    return;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }
}
