# Submission Instructions

This folder contains your actual assignment submission.

---

## Step 1 - Fill `user.sh`

Open:

```bash
user.sh
```

Fill all required details:

```bash
userDetails="here goes your info"
```

Do **not** leave this empty.

---

## Step 2 - Complete the Task

Build a **CP-Style Submission Checker** using Bash.

Your checker should simulate a competitive programming judge workflow.

---

## What Your Script Should Do

### 1. Generate Test Cases

Programmatically generate test cases for your selected problem.

You may use **any Codeforces problem** (or any similar competitive programming problem) for testing.

---

### 2. Compile & Run User Code

Your checker should compile and execute the candidate submission automatically.

Example:

```bash
./candidate < input.txt
```

If compilation fails, display the error clearly.

---

### 3. Run Reference Solution

Run the correct solution against the same testcase.

Example:

```bash
./solution < input.txt
```

---

### 4. Compare Outputs

Compare candidate output against reference output automatically.

You may use:

```bash
diff
cmp
```

or any custom comparison logic.

---

## On Failure, Show

- Testcase number
- Input used
- Expected output
- Actual output

Example:

```text
Testcase #7 FAILED

Input:
5
1 2 3 4 5

Expected:
15

Got:
14
```

The goal is to make debugging easy and informative.

---

## On Success

Display:

```text
All testcases passed
```

---

## Minimum Requirements

Your checker must:

- Compile candidate code automatically
- Generate multiple testcases
- Run both candidate and reference solution
- Compare outputs
- Report pass/fail clearly
- Print mismatch details when output differs

---

## Bonus Features (Optional)

You may additionally implement:

- Colored terminal output
- Execution timing
- Summary statistics
- Pretty diff output
- Timeout handling
- Verbose mode

These are optional and not required.

---

## Expected Deliverables

Recommended structure:

```text
submission/
├── user.sh
├── src/
│   ├── checker.sh
│   └── other source files
├── generator.sh
├── problem-content/
├── solution
└── candidate-response
```

(You may adjust structure if needed.)

---

## Submission

Push your completed work to **your respective fork**.

---

## Evaluation Criteria

You will be evaluated on:

- Correctness
- Bash proficiency
- Code clarity
- Debuggability
- Creativity
- Practical usefulness

Build something you’d actually want to use.
