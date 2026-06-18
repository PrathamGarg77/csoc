[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/b3B8Myzp)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-2e0aaae1b6195c2367325f4f02e2d04e9abb55f0b24a779b69b11b9e10269abc.svg)](https://classroom.github.com/online_ide?assignment_repo_id=23996444&assignment_repo_type=AssignmentRepo)
# CSOC ’26 Systems Programming — Week 0 + Week 1

We'll be focusing on low level programming in C: expect diving deep into networks, working extensively with pointers, and working with Linux syscalls.
For this week, just go through the resources given to you as they are quite a handful.
I expect you all to be at least somewhat familiar with C (really basic). We'll work from there.
By the end of CSoC we'll aim to implement a webserver in C. Depending on how tough or easy you feel the project is, we can rescope later, but this is the current plan.
Kindly install Linux :)))
Since this is somewhat tough to grasp, I'll be holding a meet every Sunday to talk about the tasks, take your doubts, and show how I'm implementing it.

---

Announcement

We'll be focusing on low level programming in C this season. Please go through the resources shared, install Linux, and come prepared with basic C. Sundays will be a regular doubt-solving and implementation walkthrough session. We'll close with a webserver in C by the end of CSoC.

---

## Communities

All resources, documentation, and critical updates will be shared through the CSOC website and our Discord Community.

- Registration: Ensure you are registered on the official portal.
- Discord: This is your primary office. Use the dedicated channels for queries.
- Emergency Contact: If Discord remains silent for too long, you can reach the team via WhatsApp:
  - Jayesh: 9815509240
  - Vidit: 7398089536
  - Swarit: 7379270773
  - Sebastian: +971523821819

---

## Repository Structure

```text
.
├── Resources/
├── Submission/
└── README.md
```

---

## Week 0 — Getting Started

Deadline: 23 May 2026 EOD IST

Use this time to review resources and make progress on the Week 0 goals.

---

## Systems Programming Project (2 Weeks Total)

Sunday, 24 May is the session where Week 0/Week 1 progress is discussed. After that, Week 2 starts and you have one more week for Week 2.

### Project Goal

Multithreaded Web Server in C.

### 1st Week: Static File Server with MIME, Handling and Error Responses (Week 0)

Goals:

- Serve static HTML, CSS, JS files over HTTP (GET requests only, 7-8 pages of your choice; you may use LLMs to get this over with quickly).
- Correctly set Content-Type headers based on file extension.
- Implement directory indexing (serve index.html if available).
- Return appropriate error pages (404, 403) for invalid paths.

Logging Requirements:

- Log each request in the format:
  [INFO] <timestamp> - <client_ip>:<port> - "<METHOD> <PATH> HTTP/<VERSION>" - <STATUS_CODE>
- Log server startup/shutdown.
- Log file and permission errors.

Performance Exploration (Optional):

As part of your implementation, consider observing and analyzing the time it takes to serve requests under different conditions. You're free to try and optimize this yourself. This is left as practice for the reader.

Deliverables:

- Server source files
- Example logs
- README with build and usage instructions

### 2nd Week: HTTP Request Parsing and Custom JSON Parser (Week 1)

Goals:

- Write your own HTTP request parser (no external HTTP parsing libraries).
- Parse request line, headers, and body.
- Implement a basic JSON parser from scratch (no external JSON libraries).

Logging Requirements:

- Log full request metadata:
  [REQUEST] GET /api/data HTTP/1.1
  [HEADER] Host: localhost:8080
  [BODY] { "name": "test", "value": 42 }
- Log parsing results and errors:
  [PARSE] Parsed method: GET, path: /api/data, version: HTTP/1.1
  [ERROR] Malformed request line: "BADREQUEST /foo"
  [ERROR] JSON parse error at line 1, column 14

Deliverables:

- Request and JSON parser source files
- Example input/output logs
- Test cases

### Week 2 Bonus: Thread Pool for Concurrency (Race-Free)

Goals:

- Add a fixed-size thread pool for concurrent request handling.
- Use a thread-safe task queue with std::mutex and std::condition_variable.
- Ensure thread-safe logging and global state updates (no race conditions).

Logging Requirements:

- Log worker thread activity:
  [THREAD] Worker #2 handling connection from 127.0.0.1:50328
  [THREAD] Worker #2 completed request: /home.html
- Log queue events and request count:
  [QUEUE] New connection enqueued
  [COUNTER] Request count safely incremented to 87
- Log thread pool lifecycle events:
  [INFO] Thread pool initialized with 8 workers
  [INFO] All worker threads gracefully shut down

Deliverables:

- Thread pool implementation
- Updated server with concurrency support
- Logs demonstrating concurrent handling

---

## Submission Guidelines

- All submissions live inside `Submission/`.
- For this week, keep your web server sources in the root of `Submission/` (no nested project folder).
- Use `Resources/` only for references and notes; do not place submissions there.

### Final Report

- Format: LaTeX (Overleaf recommended), submitted as PDF.
- Content: Explain your design choices and edge-case handling.
- LLM disclosure: If you use an LLM for specific logic, disclose it in the report.

---

### CSOC Website

https://csoc.copsiitbhu.co.in
