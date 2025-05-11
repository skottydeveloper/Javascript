import { Component, OnInit } from '@angular/core';
import { ReservationService } from '../reservations.service';
import { Reservation } from '../Reservation';

@Component({
  selector: 'app-reservation',
  templateUrl: './reservation.component.html',
  styleUrls: ['./reservation.component.css']
})
export class ReservationComponent implements OnInit {

  public successMsg: string;
  public errorMsg: string;
  reservationDate: string;
  name: string;
  time: string;

  constructor(private reservationService: ReservationService) { }

  ngOnInit() {
  }

  createReservation() {
    this.successMsg = '';
    this.errorMsg = '';
    this.reservationService.createReservation(this.reservationDate, this.name, this.time)
      .subscribe((createdReservation: Reservation) => {
        this.reservationDate = '';
        this.name = '';
        this.time = '';
        const reservationDate = new Date(createdReservation.reservationDate).toDateString();
        this.successMsg = `Reservation Booked Successfully for ${reservationDate}`;
      },
      (error: ErrorEvent) => {
        this.errorMsg = error.error.message;
      });
  }

}
