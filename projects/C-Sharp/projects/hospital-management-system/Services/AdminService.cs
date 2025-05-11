using Assignment_1.Models;
using Assignment_1.Utilities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assignment_1.Services
{
    public static class AdminService
    {
        // List all doctors in the system.
        public static void ListAllDoctors()
        {
            Console.Clear();

            if (Program.doctors != null && Program.doctors.Count > 0)
            {
                Console.WriteLine("List of All Doctors:");

                // Display each doctor's ID and name.
                foreach (var doctor in Program.doctors)
                {
                    Console.WriteLine($"Doctor ID: {doctor.ID}, Name: {doctor.Name}");
                }
            }
            else
            {
                Console.WriteLine("No doctors found.");
            }
        }

        // Check the details of a specific doctor by ID.
        public static void CheckDoctorDetails()
        {
            Console.Clear();
            Console.Write("Enter the ID of the doctor: ");

            int doctorID;

            try
            {
                // Parse the doctor's ID from user input.
                doctorID = int.Parse(Console.ReadLine());
            }
            catch (FormatException)
            {
                Console.WriteLine("Invalid input. Please enter a valid numeric ID.");
                return;
            }

            // Find the doctor by their ID.
            Doctor doctor = Program.doctors.Find(d => d.ID == doctorID);

            if (doctor != null)
            {
                // Display the found doctor's details.
                Console.WriteLine($"Doctor Details (ID: {doctor.ID}):");
                Console.WriteLine(doctor.ToString());
            }
            else
            {
                Console.WriteLine("Doctor not found.");
            }
        }

        // List all patients in the system.
        public static void ListAllPatients()
        {
            Console.Clear();

            if (Program.patients != null && Program.patients.Count > 0)
            {
                Console.WriteLine("List of All Patients:");

                // Display each patient's ID, name, and their assigned doctor (if any).
                foreach (var patient in Program.patients)
                {
                    string doctorName = patient.AssignedDoctor != null ? patient.AssignedDoctor.Name : "None";
                    Console.WriteLine($"Patient ID: {patient.ID}, Name: {patient.Name}, Assigned Doctor: {doctorName}");
                }
            }
            else
            {
                Console.WriteLine("No patients found.");
            }
        }

        // Check the details of a specific patient by ID.
        public static void CheckPatientDetails()
        {
            Console.Clear();
            Console.Write("Enter the ID of the patient: ");

            // Get the patient ID from user input.
            int patientID = int.Parse(Console.ReadLine());

            // Find the patient by their ID.
            Patient patient = Program.patients.Find(p => p.ID == patientID);

            if (patient != null)
            {
                // Display the found patient's details.
                Console.WriteLine($"Patient Details (ID: {patient.ID}):");
                Console.WriteLine(patient.ToString());
            }
            else
            {
                Console.WriteLine("Patient not found.");
            }
        }

        // Add a new doctor to the system.
        public static void AddDoctor()
        {
            Console.Clear();
            Console.WriteLine("Add New Doctor:");
            Console.Write("Enter Doctor Name: ");
            string name = Console.ReadLine();
            Console.Write("Enter Password: ");
            string password = Console.ReadLine();

            // Generate a new unique doctor ID.
            int newDoctorID = (Program.doctors.Count > 0) ? Program.doctors.Max(d => d.ID) + 1 : 1001;

            // Create a new doctor and add to the system.
            Doctor newDoctor = new Doctor(newDoctorID, name, password);
            Program.doctors.Add(newDoctor);

            // Save the updated list of doctors.
            FileManager.SaveDoctors(Program.doctors);
            Console.WriteLine($"Doctor {name} added successfully with ID: {newDoctorID}");
        }

        // Add a new patient to the system and assign a doctor if selected.
        public static void AddPatient()
        {
            Console.Clear();
            Console.WriteLine("Add New Patient:");
            Console.Write("Enter Patient Name: ");
            string name = Console.ReadLine();
            Console.Write("Enter Password: ");
            string password = Console.ReadLine();
            Console.WriteLine("Assign a Doctor to the Patient:");

            // Display a list of available doctors.
            for (int i = 0; i < Program.doctors.Count; i++)
            {
                Console.WriteLine($"{i + 1}. {Program.doctors[i].Name} (ID: {Program.doctors[i].ID})");
            }

            // Allow user to select a doctor to assign, or none.
            Console.Write("Enter the number of the doctor to assign (or 0 to assign none): ");
            int doctorIndex = int.Parse(Console.ReadLine()) - 1;
            Doctor assignedDoctor = null;

            if (doctorIndex >= 0 && doctorIndex < Program.doctors.Count)
            {
                assignedDoctor = Program.doctors[doctorIndex];
                Console.WriteLine($"Patient will be assigned to Dr. {assignedDoctor.Name}");
            }
            else
            {
                Console.WriteLine("No doctor assigned.");
            }

            // Generate a new unique patient ID.
            int newPatientID = (Program.patients.Count > 0) ? Program.patients.Max(p => p.ID) + 1 : 2001;

            // Create a new patient and add to the system.
            Patient newPatient = new Patient(newPatientID, name, password, assignedDoctor);
            Program.patients.Add(newPatient);

            // Save the updated list of patients.
            FileManager.SavePatients(Program.patients);
            Console.WriteLine($"Patient {name} added successfully with ID: {newPatientID}");
        }
    }
}