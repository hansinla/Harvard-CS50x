<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a stock symbol.");
        }
        else
        {
            $stock = lookup($_POST["symbol"]);
            if ($stock !== false)
            {
                render("stockdisplay.php", ["price" => $stock["price"], "symbol" => $stock["symbol"], "name" => $stock["name"] ]);
            }
            else
            {
                apologize("Sorry, that is an invalid stock symbol.");
            }
        }
    }
    else
    {
        // else render form
        render("quote_ask.php", ["title" => "Quote"]);
    }

?>
