using Assignment_1.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assignment_1.Utilities
{
    public static class AuthHandler
    {
        public static void Login() // Main login function for admins, patients and doctors.
        {
            try
            {
                Console.Clear();
                Console.WriteLine("Login to the Hospital Management System"); // Display login header information to the user.
                Console.Write("Enter ID: "); // Prompt the user to enter their ID.
                int id = int.Parse(Console.ReadLine()); // Read and parse the user's input for ID.
                Console.Write("Enter Password: "); // Prompt the user to enter their password.
                string password = ReadPassword(); // Read password securely without showing input on the screen.

                Patient patient = Program.patients.Find(p => p.ID == id && p.Password == password); // Search for the patient in the list of registered patients based on ID and password.

                if (patient != null) // If a valid patient is found, proceed with patient login.
                {
                    Console.WriteLine("Valid credentials. Logging in as Patient.");
                    MenuManager.ShowPatientMenu(patient);
                    return;
                }

                Doctor doctor = Program.doctors.Find(d => d.ID == id && d.Password == password); // Search for the doctor in the list of registered doctors based on ID and password.

                if (doctor != null) // If a valid doctor is found, proceed with doctor login.
                {
                    Console.WriteLine("Valid credentials. Logging in as Doctor.");
                    MenuManager.ShowDoctorMenu(doctor);
                    return;
                }

                Admin admin = Program.admins.Find(a => a.ID == id && a.Password == password); // Search for the admin in the list of registered admins based on ID and password.

                if (admin != null) // If a valid admin is found, proceed with doctor login.
                {
                    Console.WriteLine("Valid credentials. Logging in as Administrator.");
                    MenuManager.ShowAdminMenu(admin);
                    return;
                }

                Console.WriteLine("Invalid credentials. Please try again.");
            }
            catch (FormatException)
            {
                Console.WriteLine("Invalid ID format. Please enter a valid integer.");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"An unexpected error occurred: {ex.Message}");
            }
        }

        static string ReadPassword()
        {
            string pass = "";
            ConsoleKey key;

            do
            {
                var keyInfo = Console.ReadKey(intercept: true);
                key = keyInfo.Key;

                if (key == ConsoleKey.Backspace && pass.Length > 0) // Handle backspace: remove last character from 'pass'.
                {
                    Console.Write("\b \b");
                    pass = pass[0..^1];
                }
                else if (!char.IsControl(keyInfo.KeyChar)) // Add valid characters to pass and display '*'.
                {
                    Console.Write("*");
                    pass += keyInfo.KeyChar;
                }
            } while (key != ConsoleKey.Enter); // Loop until Enter key is pressed.

            Console.WriteLine();

            return pass; // Return the password.
        }
    }
}