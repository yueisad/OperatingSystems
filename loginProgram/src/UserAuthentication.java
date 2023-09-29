import java.io.*;
import java.util.*;
import java.text.*;
import java.net.InetAddress;

public class UserAuthentication {
    public static void main(String[] args) {
        HashMap<String, String> credentials = readCredentialsFromFile("LoginsAndPasswords.txt");

        int attempts = 0;
        boolean loggedIn = false;
        String userId = "";

        Scanner scanner = new Scanner(System.in);

        while (attempts < 3) {
            System.out.print("Enter your login ID: ");
            userId = scanner.nextLine();

            if (credentials.containsKey(userId)) {
                System.out.print("Enter your password: ");
                String password = scanner.nextLine();

                if (credentials.get(userId).equals(password)) {
                    loggedIn = true;
                    break;
                } else {
                    attempts++;
                    System.out.println("Incorrect password. Attempts remaining: " + (3 - attempts));
                    logFailedLogin(userId);
                }
            } else {
                attempts++;
                System.out.println("Invalid login ID. Attempts remaining: " + (3 - attempts));
                logFailedLogin(userId);
            }
        }

        if (loggedIn) {
            System.out.println("Login successful. Welcome, " + userId + "!");
            logSuccessfulLogin(userId);
        } else {
            System.out.println("Login failed. Your account has been locked for 1 hour.");
        }

        scanner.close();
    }

    private static HashMap<String, String> readCredentialsFromFile(String filename) {
        HashMap<String, String> credentials = new HashMap<>();

        try (Scanner fileScanner = new Scanner(new File(filename))) {
            while (fileScanner.hasNextLine()) {
                String line = fileScanner.nextLine();
                String[] parts = line.split(", ");
                credentials.put(parts[0], parts[1]);
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        return credentials;
    }

    private static void logSuccessfulLogin(String userId) {
        try (PrintWriter writer = new PrintWriter(new FileWriter("signIn.txt", true))) {
            writer.println(userId + " logged in successfully at " + getCurrentTimestamp() + " from " + getIPAddress());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void logFailedLogin(String userId) {
        try (PrintWriter writer = new PrintWriter(new FileWriter("signIn.txt", true))) {
            writer.println(userId + " attempted to log in at " + getCurrentTimestamp() + " from " + getIPAddress());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static String getCurrentTimestamp() {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        return dateFormat.format(new Date());
    }

    private static String getIPAddress() {
        try {
            InetAddress ip = InetAddress.getLocalHost();
            return ip.getHostAddress();
        } catch (Exception e) {
            return "Unknown IP";
        }
    }
}
