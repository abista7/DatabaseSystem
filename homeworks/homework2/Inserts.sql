INSERT INTO Desginations VALUES(  'Adimin'); /* Auto implemented Desg_ID */
INSERT INTO Desginations VALUES(  'Librarian'); /* Auto implemented Desg_ID */
INSERT INTO Desginations VALUES(  'Clerk'); /* Auto implemented Desg_ID */
SELECT * FROM Desginations;

INSERT INTO Staff VALUES(  'Ashraf', 'Adimin', 'Male'); /* Auto implemented Staff_ID */
INSERT INTO Staff VALUES(  'Ehsan', 'Librarian', 'Male');/* Auto implemented Staff_ID */
INSERT INTO Staff VALUES(  'Urva', 'Clerk', 'Female');/* Auto implemented Staff_ID */
SELECT * FROM Staff;

INSERT INTO Staff_Contact VALUES( 1, 'hjhs jsHVX JHVK', 'Checago', '+283498230');
INSERT INTO Staff_Contact VALUES( 2, 'hjhs jsHVX JHVK', 'Checago', '+576889223');
INSERT INTO Staff_Contact VALUES( 3 ,'nbmkuf hgcvukjv ', 'London', '+3456787334');
SELECT * FROM Staff_Contact;

INSERT INTO Department VALUES(  'Physics'); /* Auto implemented Dpt_ID */
INSERT INTO Department VALUES(  'Chemistry'); /* Auto implemented Dpt_ID */
INSERT INTO Department VALUES(  'Computer Science'); /* Auto implemented Dpt_ID */
SELECT * FROM Department


INSERT INTO Student VALUES(  'Albart ', 'Male', 1); /* Auto implemented Std_ID */
INSERT INTO Student VALUES(  'Ainstine ', 'Male', 2); /* Auto implemented Std_ID */
INSERT INTO Student VALUES(  'Ehsan ', 'Male', 3); /* Auto implemented Std_ID */
SELECT * FROM Student


INSERT INTO Student_Contact VALUES( 5, 'xfgahg ujcsVZ ','London', 'United state', '+7687968709'); 
INSERT INTO Student_Contact VALUES( 6, 'qwujbfdkj jka ', 'Checago','United Kingdom', '+235678992'); 
INSERT INTO Student_Contact VALUES( 7, 'xfgahg ujcsVZ ','Lahore', 'United state', '+0972737121'); 
SELECT * FROM Student_Contact

INSERT INTO Authors VALUES(  'Albart', 'Ainstine', 5); /* Auto implemented Author_ID */
INSERT INTO Authors VALUES( 'Ehsan', 'Tariq', 1); /* Auto implemented Author_ID */
INSERT INTO Authors VALUES(  'Ahmad', 'Faza', 3); /* Auto implemented Author_ID */
SELECT * FROM Authors


INSERT INTO Book VALUES(  'ISB12', 'Book1', 3, 'Albart', 1); /* Auto implemented Book_ID */
INSERT INTO Book VALUES(  'ISB32', 'Book2', 6, 'Ehsan', 4); /* Auto implemented Book_ID */
INSERT INTO Book VALUES(  'ISB42', 'Book3', 4, 'Ahmad', 2); /* Auto implemented Book_ID */
SELECT * FROM Book

INSERT INTO Issues VALUES(  'Book1', 1,1,'01-06-2019','01-11-2019');/* Auto implemented Issue_ID */
INSERT INTO Issues VALUES(  'Book2', 2,2,'01-01-2020','05-03-2020');/* Auto implemented Issue_ID */
INSERT INTO Issues VALUES(  'Book3', 3,3,'04-04-2020','10-11-2020'); /* Auto implemented Issue_ID */
SELECT * FROM Issues


CREATE TABLE [Return](
Return_ID INT IDENTITY(1,1) PRIMARY KEY,
Book_ID INT not null  REFERENCES Book(Book_ID),
Return_Date Date not null,
CONSTRAINT BK_ID UNIQUE (Book_ID)
)
INSERT INTO [Return] VALUES( 1, '01-11-2019'); /* Auto implemented Return_ID */
INSERT INTO [Return] VALUES( 2, '05-03-2020'); /* Auto implemented Return_ID */
INSERT INTO [Return] VALUES( 3, '10-11-2020'); /* Auto implemented Return_ID */
SELECT * FROM [Return]


 
INSERT INTO FINE_Details VALUES( 5, 300, '04-04-2020', 1); /* Auto implemented F_ID */
INSERT INTO FINE_Details VALUES( 6, 200, '12-04-2020', 2); /* Auto implemented F_ID */
INSERT INTO FINE_Details VALUES( 7, 300, '01-05-2020', 3); /* Auto implemented F_ID */
SELECT * FROM FINE_Details
