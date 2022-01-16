import { Component, OnInit } from '@angular/core';
import { ReservationService } from '../reservations.service';
import { Menu } from '../Menu';
import { mergeMap } from 'rxjs/operators';

@Component({
  selector: 'app-menu-list',
  templateUrl: './menu-list.component.html',
  styleUrls: ['./menu-list.component.css']
})
export class MenuListComponent implements OnInit {
  public loading = true;
  public items: Menu[];
  public error: string;
  public filters;
  constructor(private reservationService: ReservationService) { }

  ngOnInit(): void {
    this.reservationService.getFilters()
      .pipe(
        mergeMap(filters => {
          this.filters = filters;
          return this.reservationService.getMenuList();
        })
      )
      .subscribe((items: Menu[]) => {
        this.items = items;
        this.loading = false;
      },
      (error) => {
        this.error = error.message;
        this.loading = false;
      });
  }

  filterValues(type, value) {
    this.loading = true;
    this.reservationService.getFilteredMenuList(type, value)
      .subscribe((items: Menu[]) => {
        this.items = items;
        this.loading = false;
      },
      (error) => {
        this.error = error.message;
        this.loading = false;
      });
  }
}
