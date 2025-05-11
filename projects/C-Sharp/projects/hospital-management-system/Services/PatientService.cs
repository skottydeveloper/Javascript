using Assignment_1.Models;
using Assignment_1.Utilities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assignment_1.Services
{
    public static class PatientService
    {
        // Displays the patient's details.
        public static void ListPatientDetails(Patient patient)
        {
            Console.Clear();
            Console.WriteLine($"{patient.Name}'s Details:");
            Console.WriteLine($"Patient ID: {patient.ID}");
            Console.WriteLine(patient.ToString()); // Uses the ToString method to show patient info.
        }

        // Displays details of the doctor assigned to the patient.
        public static void ListDoctorDetails(Patient patient)
        {
            Console.Clear();

            if (patient.AssignedDoctor != null)
            {
                // Show the assigned doctor's name and ID.
                Console.WriteLine($"Your Doctor: {patient.AssignedDoctor.Name} (ID: {patient.AssignedDoctor.ID})");
            }
            else
            {
                Console.WriteLine("You are not assigned to any doctor.");
            }
        }

        // Lists all appointments of the patient.
        public static void ListAppointments(Patient patient)
        {
            Console.Clear();
            // Find all appointments associated with the patient.
            var patientAppointments = Program.appointments.FindAll(a => a.Patient == patient);

            if (patientAppointments.Count > 0)
            {
                Console.WriteLine("Your Appointments:");

                foreach (var appointment in patientAppointments)
                {
                    Console.WriteLine($"Doctor: {appointment.Doctor.Name} (ID: {appointment.Doctor.ID})");
                }
            }
            else
            {
                Console.WriteLine("You have no appointments.");
            }
        }

        // Allows the patient to book a new appointment.
        public static void BookAppointment(Patient patient)
        {
            Console.Clear();
            Doctor doctor = patient.AssignedDoctor;

            // If no doctor is assigned, prompt the patient to select a doctor.
            if (doctor == null)
            {
                Console.WriteLine("You are not registered with a doctor. Please select a doctor:");

                for (int i = 0; i < Program.doctors.Count; i++)
                {
                    // List available doctors.
                    Console.WriteLine($"{i + 1}. {Program.doctors[i].Name} (ID: {Program.doctors[i].ID})");
                }

                // Get the user's selection for a doctor.
                Console.Write("Enter the number of the doctor you want to register with: ");
                int doctorIndex = int.Parse(Console.ReadLine()) - 1;

                if (doctorIndex >= 0 && doctorIndex < Program.doctors.Count)
                {
                    doctor = Program.doctors[doctorIndex];
                    patient.AssignedDoctor = doctor; // Assign the selected doctor to the patient.
                    Console.WriteLine($"You are now registered with Dr. {doctor.Name}.");
                }
                else
                {
                    Console.WriteLine("Invalid selection.");
                    return;
                }
            }

            // Create and save a new appointment.
            Appointment newAppointment = new Appointment(doctor, patient);
            Program.appointments.Add(newAppointment);
            FileManager.SaveAppointments(Program.appointments); // Save updated appointments to file.
            Console.WriteLine($"Appointment booked successfully with Dr. {doctor.Name}.");
        }
    }
}