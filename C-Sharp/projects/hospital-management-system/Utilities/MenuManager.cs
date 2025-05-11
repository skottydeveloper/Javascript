using Assignment_1.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Assignment_1.Services;

namespace Assignment_1.Utilities
{
    public static class MenuManager
    {
        public static void ShowLoginMenu() // Displays the login menu and handles user input.
        {
            while (true)
            {
                try
                {
                    Console.Clear();
                    Console.WriteLine("Welcome to the Hospital Management System");
                    Console.WriteLine("1. Login");
                    Console.WriteLine("2. Exit");

                    string choice = Console.ReadLine();

                    switch (choice) // Handle user's menu choice.
                    {
                        case "1":
                            AuthHandler.Login(); // Call login handler.
                            break;
                        case "2":
                            Environment.Exit(0); // Exit the application.
                            break;
                        default:
                            Console.WriteLine("Invalid choice, try again.");
                            break;
                    }

                    Console.WriteLine("Press any key to continue...");
                    Console.ReadKey();
                }
                catch (UnauthorizedAccessException ex)
                {
                    Console.WriteLine($"Error: Unauthorised access. Details: {ex.Message}");
                }
                catch (IOException ex)
                {
                    Console.WriteLine($"Error: Problem with input/output operation. Details: {ex.Message}");
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"An unexpected error occurred: {ex.Message}");
                }
            }
        }

        public static void ShowPatientMenu(Patient patient) // Displays the patient menu and handles patient-specific options.
        {
            while (true)
            {
                try
                {
                    Console.Clear();
                    Console.WriteLine($"Welcome to DOTNET Hospital Management System: {patient.Name}");
                    Console.WriteLine("Please choose an option:");
                    Console.WriteLine("1. List patient details.");
                    Console.WriteLine("2. List my doctor's details.");
                    Console.WriteLine("3. List all appointments.");
                    Console.WriteLine("4. Book appointment.");
                    Console.WriteLine("5. Exit to login.");
                    Console.WriteLine("6. Exit system.");

                    string choice = Console.ReadLine();

                    switch (choice) // Handle user's menu choice for patient.
                    {
                        case "1":
                            PatientService.ListPatientDetails(patient); // Display patient details.
                            break;
                        case "2":
                        PatientService.ListDoctorDetails(patient); // Display patient's doctor details.
                            break;
                        case "3":
                        PatientService.ListAppointments(patient); // List appointments.
                            break;
                        case "4":
                        PatientService.BookAppointment(patient); // Book a new appointment.
                            break;
                        case "5":
                            return; // Exit to login menu.
                        case "6":
                            Environment.Exit(0); // Exit the system.
                            break;
                        default:
                            Console.WriteLine("Invalid choice, try again.");
                            break;
                    }

                    Console.WriteLine("Press any key to continue...");
                    Console.ReadKey();
                }
                catch (UnauthorizedAccessException ex)
                {
                    Console.WriteLine($"Error: Unauthorised access. Details: {ex.Message}");
                }
                catch (IOException ex)
                {
                    Console.WriteLine($"Error: Problem with input/output operation. Details: {ex.Message}");
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"An unexpected error occurred: {ex.Message}");
                }
            }
        }

        public static void ShowDoctorMenu(Doctor doctor) // Displays the doctor menu and handles doctor-specific options.
        {
            while (true)
            {
                try
                {
                    Console.Clear();
                    Console.WriteLine($"Welcome to DOTNET Hospital Management System: {doctor.Name}");
                    Console.WriteLine("1. List doctor details.");
                    Console.WriteLine("2. List patients.");
                    Console.WriteLine("3. List appointments.");
                    Console.WriteLine("4. Check particular patient.");
                    Console.WriteLine("5. List appointments with a patient.");
                    Console.WriteLine("6. Logout.");
                    Console.WriteLine("7. Exit.");

                    string choice = Console.ReadLine();

                    switch (choice) // Handle user's menu choice for doctor.
                    {
                        case "1":
                            DoctorService.ListDoctorDetails(doctor); // Display doctor details.
                            break;
                        case "2":
                            DoctorService.ListDoctorPatients(doctor); // List all patients.
                            break;
                        case "3":
                            DoctorService.ListDoctorAppointments(doctor); // List appointments.
                            break;
                        case "4":
                            DoctorService.CheckParticularPatient(doctor); // Check a specific patient.
                            break;
                        case "5":
                            DoctorService.ListAppointmentsWithPatient(doctor); // List appointments with a specific patient.
                            break;
                        case "6":
                            return; // Logout and return to previous menu.
                        case "7":
                            Environment.Exit(0); // Exit the system.
                            break;
                        default:
                            Console.WriteLine("Invalid choice, try again.");
                            break;
                    }

                    Console.WriteLine("Press any key to continue...");
                    Console.ReadKey();
                }
                catch (UnauthorizedAccessException ex)
                {
                    Console.WriteLine($"Error: Unauthorised access. Details: {ex.Message}");
                }
                catch (IOException ex)
                {
                    Console.WriteLine($"Error: Problem with input/output operation. Details: {ex.Message}");
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"An unexpected error occurred: {ex.Message}");
                }
            }
        }

        public static void ShowAdminMenu(Admin admin) // Displays the admin menu and handles admin-specific options.
        {
            while (true)
            {
                try 
                {
                    Console.Clear();
                    Console.WriteLine($"Welcome to DOTNET Hospital Management System: {admin.Name}");
                    Console.WriteLine("1. List all doctors.");
                    Console.WriteLine("2. Check doctor details.");
                    Console.WriteLine("3. List all patients.");
                    Console.WriteLine("4. Check patient details.");
                    Console.WriteLine("5. Add doctor.");
                    Console.WriteLine("6. Add patient.");
                    Console.WriteLine("7. Logout.");
                    Console.WriteLine("8. Exit.");

                    string choice = Console.ReadLine();

                    switch (choice)
                    {
                        case "1":
                            AdminService.ListAllDoctors(); // List all doctors.
                            break;
                        case "2":
                            AdminService.CheckDoctorDetails(); // Check a doctor's details.
                            break;
                        case "3":
                            AdminService.ListAllPatients(); // List all patients.
                            break;
                        case "4":
                            AdminService.CheckPatientDetails(); // Check a patient's details.
                            break;
                        case "5":
                            AdminService.AddDoctor(); // Add a new doctor.
                            break;
                        case "6":
                            AdminService.AddPatient(); // Add a new patient.
                            break;
                        case "7":
                            return; // Logout and return to previous menu.
                        case "8":
                            Environment.Exit(0); // Exit the system.
                            return;
                        default:
                            Console.WriteLine("Invalid choice, try again.");
                            break;
                    }

                    Console.WriteLine("Press any key to continue...");
                    Console.ReadKey();
                }
                catch (UnauthorizedAccessException ex)
                {
                    Console.WriteLine($"Error: Unauthorised access. Details: {ex.Message}");
                }
                catch (IOException ex)
                {
                    Console.WriteLine($"Error: Problem with input/output operation. Details: {ex.Message}");
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"An unexpected error occurred: {ex.Message}");
                }
            }
        }
    }
}