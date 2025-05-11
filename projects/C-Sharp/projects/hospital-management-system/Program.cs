using Assignment_1.Models;
using Assignment_1.Utilities;
using Assignment_1.Services;

namespace Assignment_1
{
    internal class Program
    {
        // Static lists to store the data for patients, doctors, admins, and appointments.
        internal static List<Patient> patients = new List<Patient>();
        internal static List<Doctor> doctors = new List<Doctor>();
        internal static List<Admin> admins = new List<Admin>();
        internal static List<Appointment> appointments = new List<Appointment>();

        static void Main(string[] args) // Main entry point of the application.
        {
            DataHandler.LoadData(); // Load all necessary data from files into memory.
            MenuManager.ShowLoginMenu();  // Display the login menu and start the application logic.
            DataHandler.SaveData();  // Save all the data back to the files when exiting the program.
        }
    }
}