public class Bicycle {
        
    // the Bicycle class has
    // three fields
    public int cadence;
    public int gear;
    public int speed;
        
    // the Bicycle class has
    // one constructor
    public Bicycle(int startCadence, int startSpeed, int startGear) {
        gear = startGear;
        cadence = startCadence;
        speed = startSpeed;
    }
        
    // the Bicycle class has
    // four methods
    public int setCadence(int newValue) {
        cadence = newValue;
        return cadence;
    }
        
    public int setGear(int newValue) {
        gear = newValue;
        return gear;
    }
        
    public int applyBrake(int decrement) {
        speed -= decrement;
        return speed;
    }
        
    public int speedUp(int increment) {
        speed += increment;
        return speed;
    }
        
}