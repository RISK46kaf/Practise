# Practise
<strong>Todo: </strong></br>
For [R] </br>
<strike>1. Create database by MySQL contains tables such as "patient", "diagnoses", "list_d", pictures", "evidences", "objects", "dye_types",  "preparation_types", "public_info" </br>
1a. diagnoses has id, name, death_rate </br>
1b. list_d (means list of diagnoses) has id, diagnosis_id(FOREIGN_KEY to id of diagnosis),public_info_id(FOREIGN_KEY to id of public_info) </br>
<i>Lis_d needs for some anonymization.</i></br>
1c. patient( is private table) has id, fullname, birth_date, sex, health_insurance_id, unique_val </br>
<i>unique_val is BLOB</i></br>
1d. pictures has id, picture, dye_types_id(FOREIGN_KEY to id of dye_types), zoom_index, preparation_types_id(FOREIGN_KEY to id of preparation_types), description, list_d_id(FOREIGN_KEY to id of list_d), is_a_part_of, top_left_coordinate  </br>
1e. evidences has id, name, picture_id(FOREIGN_KEY to id of pictures) </br>
1f. objects has id, string_data, evidence_id(FOREIGN_KEY to id of evidences) </br>
1g. dye_types has id, name  </br>
1h. preparations_types has id, name </br>
1i. public_info has id, age, sex, patient_uniq_val(FOREIGN_KEY to unique_val of patient)</br>
<i>age is <strong>NOT</strong> a birth_date: age is integer,birth_date is date </i></br></strike>
<i>Created in MySQL Workbench 6.3.3.0 32 bits</i></br>
2. Add to patient table photo as BLOB, phone_number as BIGINT, emaill as VARCHAR(255) </br></br>
3a. Change in 'patient' table 'sex' type to BOOL (coz we ain't facebook to have more then 2 variation of sex) </br>
3b. Rename in 'patient' table 'health_insurance_it' to health_insurance_id' </br>
3c. Change in 'patient' table 'birth_date' type to DATE </br>
3d. Rename in 'pictures' table 'left_top_coordinate' to 'coordinates_data' and change type of it to TEXT </br>
3e. Change in 'object' table 'string_data' type to TEXT </br>
</br>
For [I] </br>
Create program that afford:</br>
1. Read from line edit "fullname" to QString field of "patient" struct, "health_insurance_id" to int field of "patient" struct. </br>
2. Read from few spin boxes "birth_date" of patient to QDate field of "patient" struct. </br>
3. Read from few spin boxes "sex" of patient to bool field of "patient_struct".  </br>
4. Calculate SHA-256 of 1-3pp as long string data to QByteArray field of patient struct. </br>
</br>
For [S] </br>
Create program that afford:</br>
1. selected image areas </br>
2. save their type and coordinates as string_data </br>
3. save evidences list of selected areas</br>
For [K] </br>
1. Make report about diagnostics prostate oncology DSS that existing now</br>
2. Make info website based on our project scope </br>
