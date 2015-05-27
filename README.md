# Practise
<strong>Todo: </strong></br>
For [R] </br>
<strike>1. Create database by MySQL contains tables such as "patient", "diagnoses", "list_d", pictures", "evidences", "objects", "dye_types",  "preparation_types"</strike>, "public_info" </br>
<strike>1a. diagnoses has id, name, death_rate </br></strike>
1b. list_d (means list of diagnoses) has id, diagnosis_id(FOREIGN_KEY to id of diagnosis),public_info_id(FOREIGN_KEY to id of public_info) </br>
<strike><i>Lis_d needs for some anonymization.</i></br>
1c. patient( is private table) has id, fullname, birth_date, sex, health_insurance_id, unique_val </br></strike>
<i>unique_val is BLOB</i></br>
1d. pictures has id, picture, dye_types_id(FOREIGN_KEY to id of dye_types), zoom_index, preparation_types_id(FOREIGN_KEY to id of preparation_types), description, list_d_id(FOREIGN_KEY to id of list_d), is_a_part_of, top_left_coordinate  </br>
<strike>1e. evidences has id, name, picture_id(FOREIGN_KEY to id of pictures) </br>
1f. objects has id, string_data, evidence_id(FOREIGN_KEY to id of evidences) </br>
1g. dye_types has id, name  </br>
1h. preparations_types has id, name </strike> </br>
1i. public_info has id, age, sex, patient_uniq_val(FOREIGN_KEY to unique_val of patient)</br>
<i>age is <strong>NOT</strong> a birth_date: age is integer,birth_date is date </i></br>
<i>Created in MySQL Workbench 6.3.3.0 32 bits</i></br>
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
1. Make report about work was done </br>
2. Make info website based on (1) </br>
