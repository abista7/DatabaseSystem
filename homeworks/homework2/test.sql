DELETE FROM Desginations WHERE Desgination='Admin';
UPDATE Desginations SET Desgination='Checker' WHERE Desgination= 'Clerk';
SELECT Desgination FROM Desginations;

DELETE FROM Staff WHERE Desgination='Admin';
UPDATE Staff SET Desgination='Checker' WHERE Desgination= 'Clerk';
SELECT * FROM Staff;

DELETE FROM Staff_Contact WHERE City='London';
UPDATE Staff_Contact SET City='Lahore' WHERE City= 'Checago';
SELECT * FROM Staff_Contact where City ='Checago';

DELETE FROM Department WHERE Dpt_Name='Physics'; /* Cannot delete due to reference*/
UPDATE Department SET Dpt_Name='Chemistry' WHERE Dpt_Name= 'Physicology';
SELECT * FROM Department where Dpt_Name= 'Computer Science';


DELETE FROM Student; /* Cannot delete due to reference*/
UPDATE Student SET Name='Ehsan' WHERE Name= 'Usman';
SELECT Name,Student_Dpt FROM Student;


DELETE FROM Student_Contact WHERE City='Lahore'; 
UPDATE Student_Contact SET City='London' WHERE Name= 'Karachi';
SELECT City FROM Student_Contact where City='Karachi';


DELETE FROM Authors WHERE F_Name='Albart'; /* Cannot delete due to reference*/
UPDATE Authors SET F_Name='Usman' WHERE Name= 'Ehsan';
SELECT F_Name, L_Name FROM Authors;


DELETE FROM Book WHERE Book_Name='Book1'; /* Cannot delete due to reference*/
UPDATE Book SET Book_Name='Book2' WHERE Name= 'Book4';
SELECT * FROM Book where Book_Name='Book3';

DELETE FROM Issues WHERE Book_Name='Book1'; 
UPDATE Issues SET Book_Name='Book2' WHERE Name= 'Book4';
SELECT * FROM Issues;


DELETE FROM [Return] WHERE Book_ID=2; 
UPDATE [Return] SET Return_Date='10-11-2020' WHERE Return_Date= '23-12-2020';
SELECT * FROM [Return];

DELETE FROM Desginations WHERE Desgination='Admin';
UPDATE Desginations SET Desgination='Checker' WHERE Desgination= 'Clerk';
SELECT * FROM Desginations;

DELETE FROM Staff WHERE Desgination='Admin';
UPDATE Staff SET Desgination='Checker' WHERE Desgination= 'Clerk';
SELECT * FROM Staff;

DELETE FROM Staff_Contact WHERE City='London';
UPDATE Staff_Contact SET City='Lahore' WHERE City= 'Checago';
SELECT * FROM Staff_Contact;

DELETE FROM Department WHERE Dpt_Name='Physics'; /* Cannot delete due to reference*/
UPDATE Department SET Dpt_Name='Chemistry' WHERE Dpt_Name= 'Physicology';
SELECT * FROM Department;


DELETE FROM Student WHERE Name='Albart'; /* Cannot delete due to reference*/
UPDATE Student SET Name='Ehsan' WHERE Name= 'Usman';
SELECT * FROM Student;


DELETE FROM Student_Contact WHERE City='Lahore'; 
UPDATE Student_Contact SET City='London' WHERE Name= 'Karachi';
SELECT * FROM Student_Contact;


DELETE FROM Authors WHERE F_Name='Albart'; /* Cannot delete due to reference*/
UPDATE Authors SET F_Name='Usman' WHERE Name= 'Ehsan';
SELECT * FROM Authors;


DELETE FROM Book WHERE Book_Name='Book1'; /* Cannot delete due to reference*/
UPDATE Book SET Book_Name='Book2' WHERE Name= 'Book4';
SELECT * FROM Book;

DELETE FROM Issues WHERE Book_Name='Book1'; 
UPDATE Issues SET Book_Name='Book2' WHERE Name= 'Book4';
SELECT issue_Date FROM Issues;


DELETE FROM [Return] WHERE Book_ID=2; 
UPDATE [Return] SET Return_Date='10-11-2020' WHERE Return_Date= '23-12-2020';
SELECT * FROM [Return];


DELETE FROM FINE_Details WHERE Std_ID=6; 
UPDATE FINE_Details SET Due_Date='01-05-2020' WHERE Due_Date= '23-12-2020';
SELECT * FROM FINE_Details where Due_Date <'01-05-2020';
