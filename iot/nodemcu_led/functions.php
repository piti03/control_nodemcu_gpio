<?php

    // CONNECT to DATABASE
    $con = mysqli_connect("localhost","username","password","database");
    if(mysqli_connect_errno())
        echo "something went wrong". mysqli_connect_error();
    
   


// LOGIN function
function login_to_db($username, $password){
    global $con;
    // Query to find records
    $query = mysqli_query($con, "SELECT * FROM login WHERE username='$username' AND password='$password' ");

    // Check to find existed records
    if(mysqli_num_rows($query)> 0){
        
        echo "confirm the process";
    }else{
        echo "no such arguments exist in database";
    }
}



// UPDATE function 
// records are goint to receive from android side.
function board_update($firstLED, $secondLED, $thirdLED, $forthLED){
    global $con;
    // Update records in database by mobile app.
    $query = mysqli_query($con, "UPDATE mcu SET `16`='$firstLED', `5`='$secondLED', `4`='$thirdLED', `0`='$forthLED' WHERE node_id = 1");

    // Check the result
    if($query){
        echo "Record got updated successfully";
    }else{
        echo "unable to update records";
    }
}


// BOARD_FEED function
// Records are going to send to nodeMcu side.
function board_feed(){
    global $con;
    // Query to get records
    $query = mysqli_query($con, "SELECT `16`,`5`,`4`,`0` FROM mcu WHERE node_id = 1");
    if(mysqli_num_rows($query)> 0){

        // Get records as an object
        $row = mysqli_fetch_assoc($query); 

        // Turn records to the json
        return json_encode($row); 
    }else{
        return "No relevan record exists";
    }
}


?>
