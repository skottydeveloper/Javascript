using Assignment_1.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assignment_1.Services
{
    public static class DoctorService
    {
        // Display the doctor's details.
        public static void ListDoctorDetails(Doctor doctor)
        {
            Console.Clear();
            Console.WriteLine("Your Details:");
            Console.WriteLine(doctor.ToString()); // Uses ToString to display the doctor's information.
        }

        // List all patients assigned to the doctor.
        public static void ListDoctorPatients(Doctor doctor)
        {
            Console.Clear();
            // Find all patients assigned to this doctor.
            var doctorPatients = Program.patients.FindAll(p => p.AssignedDoctor == doctor);

            if (doctorPatients.Count > 0)
            {
                Console.WriteLine("Your Patients:");

                // Display the details of each assigned patient.
                foreach (var patient in doctorPatients)
                {
                    Console.WriteLine($"Patient ID: {patient.ID}, Name: {patient.Name}");
                }
            }
            else
            {
                Console.WriteLine("You have no assigned patients.");
            }
        }

        // List all appointments for the doctor.
        public static void ListDoctorAppointments(Doctor doctor)
        {
            Console.Clear();
            // Find all appointments associated with this doctor.
            var doctorAppointments = Program.appointments.FindAll(a => a.Doctor == doctor);

            if (doctorAppointments.Count > 0)
            {
                Console.WriteLine("Your Appointments:");

                // Display appointment details including patient information.
                foreach (var appointment in doctorAppointments)
                {
                    Console.WriteLine($"Patient: {appointment.Patient.Name} (ID: {appointment.Patient.ID})");
                }
            }
            else
            {
                Console.WriteLine("You have no appointments.");
            }
        }

        // Check details of a specific patient assigned to the doctor by patient ID.
        public static void CheckParticularPatient(Doctor doctor)
        {
            Console.Clear();
            Console.Write("Enter the ID of the patient to check: ");

            int patientID;

            try
            {
                // Parse the input to get the patient ID.
                patientID = int.Parse(Console.ReadLine());
            }
            catch (FormatException)
            {
                Console.WriteLine("Invalid input. Please enter a valid numeric ID.");
                return;
            }

            // Find the patient with the given ID and ensure the patient is assigned to the doctor.
            Patient patient = Program.patients.Find(p => p.ID == patientID && p.AssignedDoctor == doctor);

            if (patient != null)
            {
                // Display patient details if found.
                Console.WriteLine($"Patient Details (ID: {patient.ID}):");
                Console.WriteLine(patient.ToString());
            }
            else
            {
                Console.WriteLine("No patient found with that ID, or the patient is not assigned to you.");
            }
        }

        // List all appointments with a specific patient.
        public static void ListAppointmentsWithPatient(Doctor doctor)
        {
            Console.Clear();
            Console.Write("Enter the ID of the patient to check appointments with: ");

            int patientID;

            try
            {
                // Parse the input to get the patient ID.
                patientID = int.Parse(Console.ReadLine());
            }
            catch (FormatException)
            {
                Console.WriteLine("Invalid input. Please enter a valid numeric ID.");
                return;
            }

            // Find the patient with the given ID and ensure the patient is assigned to the doctor.
            Patient patient = Program.patients.Find(p => p.ID == patientID && p.AssignedDoctor == doctor);

            if (patient != null)
            {
                // Find all appointments between this doctor and the specific patient.
                var patientAppointments = Program.appointments.FindAll(a => a.Patient == patient && a.Doctor == doctor);

                if (patientAppointments.Count > 0)
                {
                    Console.WriteLine($"Appointments with Patient: {patient.Name} (ID: {patient.ID}):");

                    // Display each appointment with the patient.
                    foreach (var appointment in patientAppointments)
                    {
                        Console.WriteLine(appointment.ToString());
                    }
                }
                else
                {
                    Console.WriteLine("No appointments found with this patient.");
                }
            }
            else
            {
                Console.WriteLine("No patient found with that ID or the patient is not assigned to you.");
            }
        }
    }
}