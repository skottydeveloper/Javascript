using Assignment_1.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Assignment_1.Utilities
{
    public static class DataHandler
    {
        public static void LoadData() // Method to load data from files into program variables.
        {
            try
            {
                // Load data into respective collections from file.
                Program.doctors = FileManager.LoadDoctors();
                Program.patients = FileManager.LoadPatients(Program.doctors);
                Program.admins = FileManager.LoadAdmins();
                Program.appointments = FileManager.LoadAppointments(Program.doctors, Program.patients);
            }
            catch (FileNotFoundException ex)
            {
                Console.WriteLine($"Error: File not found. Details: {ex.Message}");
            }
            catch (UnauthorizedAccessException ex)
            {
                Console.WriteLine($"Error: Unauthorized access. Details: {ex.Message}");
            }
            catch (IOException ex)
            {
                Console.WriteLine($"Error: Problem with file I/O. Details: {ex.Message}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"An unexpected error occurred: {ex.Message}");
            }
        }

        public static void SaveData() // Method to save program data back into files.
        {
            try
            {
                // Save data from collections into files.
                FileManager.SaveDoctors(Program.doctors);
                FileManager.SavePatients(Program.patients);
                FileManager.SaveAdmins(Program.admins);
                FileManager.SaveAppointments(Program.appointments);
            }
            catch (FileNotFoundException ex)
            {
                Console.WriteLine($"Error: File not found. Details: {ex.Message}");
            }
            catch (UnauthorizedAccessException ex)
            {
                Console.WriteLine($"Error: Unauthorized access. Details: {ex.Message}");
            }
            catch (IOException ex)
            {
                Console.WriteLine($"Error: Problem with file I/O. Details: {ex.Message}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"An unexpected error occurred: {ex.Message}");
            }
        }
    }
}