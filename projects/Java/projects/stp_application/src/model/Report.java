package model;

import javafx.beans.property.DoubleProperty;
import javafx.beans.property.ReadOnlyDoubleProperty;
import javafx.beans.property.ReadOnlyStringProperty;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

/**
 *
 * @author George
 */
public class Report {

    private StringProperty name;
    private DoubleProperty wages;
    private DoubleProperty tax;
    private DoubleProperty net;
    private DoubleProperty superannuation;

    public Report(Employee e) {
        this.name = new SimpleStringProperty();
        this.name.set(e.getName());
        this.wages = new SimpleDoubleProperty();
        this.wages.set(e.getIncome());
        this.tax = new SimpleDoubleProperty();
        tax.set(e.getDeduction());
        this.net = new SimpleDoubleProperty();
        net.set(e.getNet());
        this.superannuation = new SimpleDoubleProperty();
        superannuation.set(e.getSuper());
    }

    public ReadOnlyStringProperty nameProperty() {
        return name;
    }

    public String getName() {
        return name.getValue();
    }

    public ReadOnlyDoubleProperty wagesProperty() {
        return wages;
    }

    public double getWages() {
        return wages.get();
    }

    public ReadOnlyDoubleProperty taxProperty() {
        return tax;
    }

    public double getTax() {
        return tax.get();
    }

    public ReadOnlyDoubleProperty netProperty() {
        return net;
    }

    public double getNet() {
        return net.get();
    }

    public ReadOnlyDoubleProperty superannuationProperty() {
        return superannuation;
    }

    public double getSuperannuation() {
        return superannuation.get();
    }
}
