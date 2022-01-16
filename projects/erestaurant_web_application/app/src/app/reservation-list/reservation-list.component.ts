import { Component, OnInit } from '@angular/core';
import { ReservationService } from '../reservations.service';
import { Reservation } from '../Reservation';
import { mergeMap } from 'rxjs/operators';

@Component({
  selector: 'app-reservation-list',
  templateUrl: './reservation-list.component.html',
  styleUrls: ['./reservation-list.component.css']
})
export class ReservationListComponent implements OnInit {

  public loading = true;
  public errorMsg: string;
  public successMsg: string;
  public reservations: Reservation[];
  public columns = ['reservationDate', 'name', 'time', 'cancel'];

  constructor(private reservationService: ReservationService) { }

  ngOnInit() {
    this.reservationService.getReservations()
      .subscribe((reservations: Reservation[]) => {
        this.reservations = reservations;
        this.loading = false;
      },
      (error: ErrorEvent) => {
        this.errorMsg = error.error.message;
        this.loading = false;
      });
  }

  cancelReservation(id: string) {
    this.reservationService.cancelReservation(id)
      .pipe(
        mergeMap(() => this.reservationService.getReservations())
      )
      .subscribe((reservations: Reservation[]) => {
        this.reservations = reservations;
        this.successMsg = 'Successfully cancelled the reservation';
      },
      (error: ErrorEvent) => {
        this.errorMsg = error.error.message;
      });
  }

}

