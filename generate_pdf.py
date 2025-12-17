import os
import subprocess
from fpdf import FPDF

# Configuration
ASSIGNMENT_DIR = "sem3/assignment/a1"
OUTPUT_PDF = "assignment_a1.pdf"
FILES = ["q1.c", "q2.c", "q3.c", "q4.c", "q5.c"]

# Test inputs for each program
INPUTS = {
    "q1.c": "5\n10 20 5 50 15\n",
    "q2.c": "5\n1 2 3 4 5\n",
    "q3.c": "5\n1 2 3 4 5\n5\n3 4 5 6 7\n",
    "q4.c": "5\n1 2 3 4 5\n2\n1\n", # Rotate left by 2
    "q5.c": "4\n1 2 4 5\n" # Missing 3 from 1-5
}

class PDF(FPDF):
    def header(self):
        self.set_font('Arial', 'B', 12)
        self.cell(0, 10, 'Assignment 1', 0, 1, 'C')
        self.ln(5)

    def chapter_title(self, title):
        self.set_font('Arial', 'B', 12)
        self.set_fill_color(200, 220, 255)
        self.cell(0, 6, title, 0, 1, 'L', 1)
        self.ln(4)

    def chapter_body(self, body, font_family='Courier', size=10):
        self.set_font(font_family, '', size)
        self.multi_cell(0, 5, body)
        self.ln()

def extract_question(filepath):
    """Extracts the question from the top comment block of the C file."""
    question = []
    with open(filepath, 'r') as f:
        lines = f.readlines()
        in_comment = False
        for line in lines:
            line = line.strip()
            if line.startswith("/*"):
                in_comment = True
                continue
            if line.endswith("*/"):
                in_comment = False
                break
            if in_comment:
                # Remove leading * and spaces
                cleaned = line.lstrip('*').strip()
                if cleaned:
                    question.append(cleaned)
    return " ".join(question)

def compile_and_run(filepath, input_str):
    """Compiles and runs the C program, returning the output."""
    exe_path = filepath.replace(".c", ".exe")
    
    # Compile
    compile_cmd = ["gcc", filepath, "-o", exe_path]
    compile_proc = subprocess.run(compile_cmd, capture_output=True, text=True)
    
    if compile_proc.returncode != 0:
        return f"Compilation Error:\n{compile_proc.stderr}"
    
    # Run
    try:
        run_proc = subprocess.run([exe_path], input=input_str, capture_output=True, text=True, timeout=5)
        output = run_proc.stdout
    except subprocess.TimeoutExpired:
        output = "Execution Timed Out"
    except Exception as e:
        output = f"Execution Error: {str(e)}"
    
    # Clean up exe
    if os.path.exists(exe_path):
        os.remove(exe_path)
        
    return output

def main():
    pdf = PDF()
    pdf.set_auto_page_break(auto=True, margin=15)
    
    # Add a title page
    pdf.add_page()
    pdf.set_font('Arial', 'B', 16)
    pdf.cell(0, 20, 'Assignment 1 Report', 0, 1, 'C')
    pdf.ln(20)
    
    for filename in FILES:
        filepath = os.path.join(ASSIGNMENT_DIR, filename)
        if not os.path.exists(filepath):
            print(f"File not found: {filepath}")
            continue
            
        print(f"Processing {filename}...")
        
        # 1. Extract Question
        question = extract_question(filepath)
        
        # 2. Read Code
        with open(filepath, 'r') as f:
            code = f.read()
            
        # 3. Execute
        input_data = INPUTS.get(filename, "")
        output = compile_and_run(filepath, input_data)
        
        # 4. Format PDF
        pdf.add_page()
        
        # Question Section
        pdf.chapter_title(f'Problem: {filename}')
        pdf.set_font('Arial', 'I', 11)
        pdf.multi_cell(0, 5, question)
        pdf.ln(5)
        
        # Code Section
        pdf.chapter_title('Source Code')
        pdf.chapter_body(code, size=8)
        
        # Output Section
        pdf.chapter_title('Execution Output')
        # Show input used if any
        if input_data:
            input_display = input_data.replace('\n', ' ')
            pdf.set_font('Courier', 'I', 9)
            pdf.cell(0, 5, f"Input provided: {input_display}", 0, 1)
            pdf.ln(2)
            
        pdf.chapter_body(output, size=9)

    pdf.output(OUTPUT_PDF)
    print(f"PDF generated: {OUTPUT_PDF}")

if __name__ == "__main__":
    main()
