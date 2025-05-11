
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq.Expressions;
using Assignment_1.Models;

namespace Assignment_1.Utilities
{
    public static class FileManager
    {
        // File paths for storing different data types.
        private static string adminFilePath = "admins.txt";
        private static string doctorFilePath = "doctors.txt";
        private static string patientFilePath = "patients.txt";
        private static string appointmentFilePath = "appointments.txt";

        public static void SaveDoctors(List<Doctor> doctors) // Save doctor data to file.
        {
            try
            {
                using (StreamWriter writer = new StreamWriter(doctorFilePath))
                {
                    foreach (var doctor in doctors)
                    {
                        writer.WriteLine($"{doctor.ID},{doctor.Name},{doctor.Password}");
                    }
                }
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

        public static List<Doctor> LoadDoctors() // Load doctor data from file.
        {
            var doctors = new List<Doctor>();

            try
            {
                if (!File.Exists(doctorFilePath)) return doctors;

                foreach (var line in File.ReadAllLines(doctorFilePath))
                {
                    string[] data = line.Split(',');

                    if (data.Length == 3)
                    {
                        Doctor doctor = new Doctor(int.Parse(data[0]), data[1], data[2]);
                        doctors.Add(doctor);
                    }
                }
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

            return doctors;
        }

        public static void SavePatients(List<Patient> patients) // Save patient data to file.
        {
            try
            {
                using (StreamWriter writer = new StreamWriter(patientFilePath))
                {
                    foreach (var patient in patients)
                    {
                        string doctorID = patient.AssignedDoctor != null ? patient.AssignedDoctor.ID.ToString() : "None";
                        writer.WriteLine($"{patient.ID},{patient.Name},{patient.Password},{doctorID}");
                    }
                }
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

        public static List<Patient> LoadPatients(List<Doctor> doctors) // Load patient data from file.
        {
            var patients = new List<Patient>();

            try
            {
                if (!File.Exists(patientFilePath)) return patients;

                foreach (var line in File.ReadAllLines(patientFilePath))
                {
                    string[] data = line.Split(',');

                    if (data.Length == 4)
                    {
                        Doctor assignedDoctor = doctors.Find(doc => doc.ID.ToString() == data[3]);
                        Patient patient = new Patient(int.Parse(data[0]), data[1], data[2], assignedDoctor);
                        patients.Add(patient);
                    }
                }
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

            return patients;
        }

        public static void SaveAppointments(List<Appointment> appointments) // Save appointment data to file.
        {
            try
            {
                using (StreamWriter writer = new StreamWriter(appointmentFilePath))
                {
                    foreach (var appointment in appointments)
                    {
                        writer.WriteLine($"{appointment.Doctor.ID},{appointment.Patient.ID}");
                    }
                }
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

        public static List<Appointment> LoadAppointments(List<Doctor> doctors, List<Patient> patients) // Load appointment data from file.
        {
            var appointments = new List<Appointment>();

            try
            {
                if (!File.Exists(appointmentFilePath)) return appointments;

                foreach (var line in File.ReadAllLines(appointmentFilePath))
                {
                    string[] data = line.Split(',');

                    if (data.Length == 2)
                    {
                        Doctor doctor = doctors.Find(doc => doc.ID.ToString() == data[0]);
                        Patient patient = patients.Find(pat => pat.ID.ToString() == data[1]);

                        if (doctor != null && patient != null)
                        {
                            appointments.Add(new Appointment(doctor, patient));
                        }
                    }
                }
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

            return appointments;
        }

        public static void SaveAdmins(List<Admin> admins) // Save admin data to file.
        {
            try
            {
                using (StreamWriter writer = new StreamWriter(adminFilePath))
                {
                    foreach (var admin in admins)
                    {
                        writer.WriteLine($"{admin.ID},{admin.Name},{admin.Password}");
                    }
                }
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

        public static List<Admin> LoadAdmins() // Load admin data from file.
        {
            var admins = new List<Admin>();

            try
            {
                if (!File.Exists(adminFilePath)) return admins;

                foreach (var line in File.ReadAllLines(adminFilePath))
                {
                    string[] data = line.Split(',');

                    if (data.Length == 3)
                    {
                        Admin admin = new Admin(int.Parse(data[0]), data[1], data[2]);
                        admins.Add(admin);
                    }
                }
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

            return admins;
        }
    }
}