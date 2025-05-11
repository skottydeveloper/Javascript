package model;

/**
 *
 * @author George
 */
public class Session {
    private Employer employer;
    private Employers employers;
    
    public Session(){
        this.employers = new Employers(); 
        this.employer = new Employer();
    }
 
    public Employer getEmployer(String email, String password){
        return employers.getEmployer(email, password);
    }
    
    public void setEmployer(Employer e){
        this.employer = e;
    }
}
