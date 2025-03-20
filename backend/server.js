const express = require("express");
const multer = require("multer");
const cors = require("cors");
const { exec } = require("child_process");
const path = require("path");
const fs = require("fs");

const app = express();
app.use(cors());

// Configure multer to save uploaded files to 'uploads/' directory
const upload = multer({ dest: "uploads/" });

// API endpoint to handle file uploads
app.post("/upload", upload.single("file"), (req, res) => {
    if (!req.file) {
        return res.status(400).json({ error: "No file uploaded" });
    }

    // Get the uploaded file path
    const filePath = path.join(__dirname, req.file.path);

    console.log("Processing file:", filePath);

    // Run the C++ program with the file path as an argument
    exec(`./markov "${filePath}"`, (error, stdout, stderr) => {
        if (error) {
            console.error(`Execution Error: ${stderr}`);
            return res.status(500).json({ error: "Processing failed", details: stderr });
        }

        console.log(`Program Output: ${stdout}`);

        // Send the output back to the client
        res.json({ message: "File processed successfully", output: stdout });

        // Optional: Delete the file after processing to free up space
        fs.unlink(filePath, (err) => {
            if (err) console.error("Error deleting file:", err);
            else console.log("Temporary file deleted:", filePath);
        });
    });
});

// Start the server
const PORT = 8080;
app.listen(PORT, () => console.log(`Server running on port ${PORT}`));
