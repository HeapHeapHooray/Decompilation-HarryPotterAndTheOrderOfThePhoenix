import json
import struct

def scan_functions(filename, output_filename):
    with open(filename, 'rb') as f:
        data = f.read()

    # .text section info from objdump
    # Idx Name          Size      VMA       LMA       File off  Algn
    #   0 .text         003b500f  00401000  00401000  00001000  2**2
    
    section_offset = 0x1000
    section_size = 0x3b500f
    section_vma = 0x401000
    
    # HATRED section info
    # 4 HATRED        000504cb  00e78000  00e78000  004dc000  2**2
    hatred_offset = 0x4dc000
    hatred_size = 0x504cb
    hatred_vma = 0xe78000

    sections = [
        (data[section_offset : section_offset + section_size], section_vma),
        (data[hatred_offset : hatred_offset + hatred_size], hatred_vma)
    ]
    
    # Common function prologue: push ebp; mov ebp, esp
    prologue = b'\x55\x8b\xec'
    
    function_addresses = []
    
    for section_data, base_vma in sections:
        # Simple scan
        offset = 0
        while True:
            try:
                index = section_data.index(prologue, offset)
                # Calculate Virtual Address
                # relative offset in section + section VMA
                va = index + base_vma
                function_addresses.append(hex(va))
                offset = index + 1
            except ValueError:
                break
            
    print(f"Found {len(function_addresses)} possible functions.")
    
    with open(output_filename, 'w') as f:
        json.dump(function_addresses, f, indent=4)

if __name__ == '__main__':
    scan_functions('hp.exe', 'functions.json')
