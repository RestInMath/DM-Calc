import sys, subprocess
from PyQt5.QtWidgets import *
from PyQt5 import QtCore


def get_type(inp):
    if inp[0] == 'A': return 'A', inp[2:]
    if 'x' in inp: return 'P', inp
    else: return 'F', inp


def parse_input_nat(inp):
    nums, ops = [],[]
    inp = inp.split(' ')
    for i in inp:
        if i in ['+','-','*','/', '%', '//', 'K', 'D']:
            ops.append(i)
        else:
            nom = i
            den = '1'
            if '/' in i:
                nom = i[:i.index('/')]
                den = i[i.index('/')+1:][::-1]

            if nom[0] == '+':
                nom = nom[1:][::-1]
            else:
                nom = nom[::-1]

            nums.append(nom)
            nums.append(den)
    return nums, ops

def parse_input_pol(inp):
    nums, ops, nums2 = [], [], []
    inp = inp.split(' ')
    for i in inp:
        if i in ['+', '-', '/', '*']:
            ops.append(i)
            nums2 = list(nums)
            nums = []
            continue

        if 'x' in i:
            deg = i[i.index('x') + 1:]
            i = i[:-len(deg)-1]
            if deg == '': deg = '1'
        else:
            deg = '0'

        nom = i
        den = '1'

        if '/' in i:
            nom = i[:i.index('/')]
            den = i[i.index('/')+1:]

        if nom[0] == '+':
            nom = nom[1:][::-1]
        else:
            nom = nom[::-1]

        nums.append(nom)
        nums.append(den)
        nums.append(deg)
    return nums2, ops, nums

def sendP(type, nums, op, nums2):
    result = subprocess.run(['COLOCOUS.exe', type, op[0], *nums, op[0], *nums2, op[0]], stdout = subprocess.PIPE)
    result = result.stdout.decode('utf-8')
    return result

def send(type, nums, ops):
    result = subprocess.run(['COLOCOUS.exe', type, *nums, ops[0]], stdout = subprocess.PIPE) #should send 4 nums
    result = result.stdout.decode('utf-8')
    return result

class CalcWin(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        exitAction = QAction(self)
        exitAction.setShortcut("Ctrl+Return")
        exitAction.triggered.connect(self.butClicked)
        self.addAction(exitAction)

        self.exEdit = QTextEdit(self)
        self.exEdit.resize(850,180)

        self.eqBut = QPushButton(self)
        self.eqBut.setGeometry(50,200, 80,25)
        self.eqBut.setText('=')
        self.eqBut.setToolTip('Hot Key: Ctrl + Enter')

        self.resField = QTextBrowser(self)
        self.resField.setGeometry(0,250, 850, 180)
        self.resField.setText("...")

        self.eqBut.clicked.connect(self.butClicked)

        self.setFixedSize(850, 500)
        self.setWindowTitle('Calculator')
        self.show()

    def butClicked(self):
        try:
            inpText = self.exEdit.toPlainText()
            type, inpText = get_type(inpText)
            if type == 'P':
                send_nums, send_ops, send_nums2 = parse_input_pol(inpText)
                out_text = sendP(type, send_nums, send_ops, send_nums2)
            else:
                send_nums, send_ops = parse_input_nat(inpText)
                out_text = send(type, send_nums, send_ops)
            self.resField.setText(out_text)
        except:
            self.resField.setText("Неверный ввод")

if __name__ == '__main__':

    app = QApplication(sys.argv)
    win = CalcWin()
    sys.exit(app.exec_())