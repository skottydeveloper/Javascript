import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { Reservation } from './Reservation';
import { Menu } from './Menu';
import { environment } from 'src/environments/environment';

@Injectable({
  providedIn: 'root'
})
export class ReservationService {

  private BASE_URL = environment.API_URL;

  constructor(private http: HttpClient) { }

  getReservations(): Observable<Reservation[]> {
    return this.http.get<Reservation[]>(`${this.BASE_URL}/reservations/reservations`);
  }

  createReservation(reservationDate: string, name: string, time: string): Observable<Reservation> {
    return this.http.post<Reservation>(`${this.BASE_URL}/reservations/reservations`, { reservationDate, name, time });
  }

  cancelReservation(id: string): Observable<any> {
    return this.http.delete(`${this.BASE_URL}/reservations/reservations/${id}`);
  }
  getMenuList(): Observable<Menu[]>{
    return this.http.get<Menu[]>(`${this.BASE_URL}/menu/menu`);
  }
  getFilteredMenuList(type: string, value: string): Observable<Menu[]> {
    return this.http.get<Menu[]>(`${this.BASE_URL}/menu/filter/${type}/${value}`);
  }
  getFilters(){
    return this.http.get(`${this.BASE_URL}/menu/filters`);
  }
  getMenu(id: string): Observable<Menu> {
    return this.http.get<Menu>(`${this.BASE_URL}/menu/menu/${id}`);
  }



}
