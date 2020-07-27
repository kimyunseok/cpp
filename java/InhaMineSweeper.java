package minesweeper;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.Serializable;
import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
/*
 *  인하대학교 2020-1학기 자바기반응용프로그래밍 과제
 *  지뢰찾기 구현
 *  구현목록 : 게임 기본기능, 타이머, 저장, 불러오기, 난이도 설정, 랭킹
 *  아쉬운 점은 원래는 클래스 내부에는 뼈대만 생성하고 기능들은 public class에서 구현하려 했으나 잘 안된 점
 */
public class InhaMineSweeper extends JFrame implements Serializable{
	MineSweeperMenuBar mb;
	NorthPart north;
	CenterPart center;
	ArrayList<Ranking> rank;
	
	public InhaMineSweeper() {
	BorderLayout layout = new BorderLayout();
	setTitle("지뢰찾기");
	setLayout(layout);
	north = new NorthPart();
	add(north, BorderLayout.NORTH);
	center = new CenterPart();
	add(center, BorderLayout.CENTER);
	rank = new ArrayList<Ranking>();
	makeMenuBar();
	try(DataInputStream disr = new DataInputStream(new FileInputStream("C:\\Download\\InhaMineSweeperRank.dat"))) {
		int len = disr.read();
		for(int i = 0; i < len; i++) {
			rank.add(new Ranking(disr.readUTF(), disr.read(), disr.read()));
		}
		Collections.sort(rank);
	}catch (IOException e) {
		e.printStackTrace();
	}
	
	setSize(450, 500);
	setDefaultCloseOperation(EXIT_ON_CLOSE);
	setVisible(true);
	}
	
	/*
	 * 상단바의 기능에 대한 구현기능
	 *  저장, 불러오기, 도움말, 난이도에 대한 기능이 구현되어있음.
	 */
	void makeMenuBar() {
		mb = new MineSweeperMenuBar();
		setJMenuBar(mb);
		mb.exitGame.addActionListener(new ActionListener() { // 게임종료 액션리스너
			@Override
			public void actionPerformed(ActionEvent e) {
				int result;
				result = JOptionPane.showConfirmDialog(InhaMineSweeper.this, "게임을 종료하시겠습니까?\n저장하지 않은 정보는 모두 사라집니다.", "게임종료", 
															JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE );
				if ( result == JOptionPane.YES_OPTION ) System.exit(0);
			}
		});
		mb.helper.addActionListener(new ActionListener() { // 도움말 액션리스너
			
			@Override
			public void actionPerformed(ActionEvent e) {
				JOptionPane.showMessageDialog(InhaMineSweeper.this, "만든 이 : 인하대학교 김현석 \n학번 : 12171608\n만든날짜 : 2020-06-24\n\n지뢰찾기의 목표는 "
						+ "\n모든 지뢰를 밟지 않고\n빈 부분을 모두 찾는 것입니다.\n지뢰를 하나라도 밟게 되면\n게임에서 지게 됩니다.", "도움말", 
						JOptionPane.INFORMATION_MESSAGE );
			}
		});
		mb.ranking.addActionListener(new ActionListener() { // 랭킹구현 리스너
			@Override
			public void actionPerformed(ActionEvent e) {
				StringBuilder rankMaker = new StringBuilder();
				rankMaker.append("순위  |  난이도  |   시간   |    점수\n");
				for(int i = 0; i < rank.size(); i++) {
					rankMaker.append( (i+1) + "위        " + rank.get(i).level + "         " + rank.get(i).clearTime + "초      " + rank.get(i).clearScore + "점" + "\n");
				}
				String ranking = "" + rankMaker;
				JOptionPane.showMessageDialog(InhaMineSweeper.this, (rankMaker.equals("") ? "랭킹정보가 없습니다!" : ranking), "랭킹", 
						JOptionPane.INFORMATION_MESSAGE );
			}
		});
		
		ActionListener play = new ActionListener() { // 새 게임 액션리스너 - 버튼을 만듦
			
			@Override
			public void actionPerformed(ActionEvent e) {
				north.setTimerText(0);
				north.firstTouch = true;
				north.timePass = false;
				north.reset.setText("'_'");
				if(e.getSource() == mb.easy) {
					center.makeButton(1);
					add(center, BorderLayout.CENTER);
					setSize(450, 500);
				} else if(e.getSource() == mb.normal) {
					center.makeButton(2);
					add(center, BorderLayout.CENTER);
					setSize(450, 800);
				} else {
					center.makeButton(3);
					add(center, BorderLayout.CENTER);
					setSize(900, 1000);
				}
				north.setMinesNumText(center.thisIsMine);
			}
		};
		mb.easy.addActionListener(play);
		mb.normal.addActionListener(play);
		mb.hard.addActionListener(play);
		ActionListener saveLoad = new ActionListener() { // 저장과 불러오기를 담당하는 리스너
			
			@Override
			public void actionPerformed(ActionEvent e) { 
				if(e.getSource() == mb.saveGame) { // 저장하기 
					if(center.gameOver || ( ((center.lvl == 1 && center.gameClear == 90) || (center.lvl == 2 && center.gameClear == 160) || (center.lvl == 3 && center.gameClear == 500)) 
							&& center.thisIsMine >= 0 )) { // 게임오버, 클리어 상태에서는 저장 불가
						JOptionPane.showMessageDialog(InhaMineSweeper.this, "게임 오버 혹은 게임  클리어 상태는 저장할 수 없습니다.", 
								"저장 실패", JOptionPane.INFORMATION_MESSAGE );
					}
					else { // 게임오버, 클리어 상태가 아닐 경우
					int save = JOptionPane.showConfirmDialog(InhaMineSweeper.this, "게임을 저장하시겠습니까?\n기존 저장했던 데이터는 사라집니다.", "게임저장", 
																JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE );
					if ( save == JOptionPane.YES_OPTION ) {
					try(DataOutputStream dos = new DataOutputStream(new FileOutputStream("C:\\Download\\InhaMineSweeper.sav"))) {
						north.timePass = false;
						north.firstTouch = true;
						dos.write(center.lvl);
						dos.write(center.minesNum.length);
						for(int i = 0; i < center.minesNum.length; i++) {
						dos.writeInt(center.minesNum[i]);
						}
						dos.write(center.thisIsMine);
						dos.write(north.time);
						dos.writeUTF(north.reset.getText());
						dos.write(center.gameClear);
						for(int i = 0; i < center.buttons.length; i++) {
							dos.writeBoolean(center.buttons[i].isOpaque());
							dos.writeBoolean(center.buttons[i].isEnabled());
							dos.writeBoolean(center.buttons[i].isSelected());
							dos.writeUTF(center.buttons[i].getText());
						}
						JOptionPane.showMessageDialog(InhaMineSweeper.this, "게임을 C:\\Download 폴더에 저장하였습니다. ", "SAVE GAME", 
								JOptionPane.INFORMATION_MESSAGE );
					} catch (IOException err) {
						JOptionPane.showMessageDialog(InhaMineSweeper.this, "저장하지 못 하였습니다.", "저장오류", JOptionPane.INFORMATION_MESSAGE );
						err.printStackTrace();
					}
					}
					}
				} else { // 불러오기
					int load = JOptionPane.showConfirmDialog(InhaMineSweeper.this, "게임을 불러오시겠습니까?\n진행중이던 데이터는 사라집니다.", "게임 불러오기", 
							JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE );
					if ( load == JOptionPane.YES_OPTION ) {
					try(DataInputStream dis = new DataInputStream(new FileInputStream("C:\\Download\\InhaMineSweeper.sav"))) {
						north.timePass = false;
						north.firstTouch = true;	
						center.gameLoad = true;
						int lvl = dis.read();
						int mineLen = dis.read();
						int buttonLen;;
						center.lvl = lvl;
						if (center.lvl == 1) {
							setSize(450, 500);
							center.minesNum = new int[10];
							buttonLen = 100;
						}else if (center.lvl == 2) {
							setSize(450, 800);
							center.minesNum = new int[40];
							buttonLen = 200;
						} else {
							setSize(900, 1000);
							center.minesNum = new int[100];
							buttonLen = 600;
						}
						for(int i = 0; i < mineLen; i++) {
							center.minesNum[i] = dis.readInt();
							}
						center.makeButton(lvl);
						center.thisIsMine = dis.read();
						north.time = dis.read();
						north.setTimerText(north.time);
						north.setMinesNumText(center.thisIsMine);
						north.reset.setText(dis.readUTF());
						center.gameClear = dis.read();
						center.gameLoad = false;
						for(int i = 0; i < buttonLen; i++) {
							center.buttons[i].setOpaque(dis.readBoolean());
							center.buttons[i].setEnabled(dis.readBoolean());
							center.buttons[i].setSelected(dis.readBoolean());
							center.buttons[i].setText(dis.readUTF());
							if(center.buttons[i].isOpaque() && center.buttons[i].isSelected() &&!center.buttons[i].isEnabled()) {
								center.buttons[i].setBackground(Color.LIGHT_GRAY);
							} else if(center.buttons[i].isOpaque() && !center.buttons[i].isEnabled()) {
								center.buttons[i].setBackground(Color.BLUE);
							}
						}
						center.revalidate();
						JOptionPane.showMessageDialog(InhaMineSweeper.this, "게임을 C:\\Download 폴더에서 불러왔습니다. ", "LOAD GAME", 
								JOptionPane.INFORMATION_MESSAGE );
					}
					catch (IOException err) {
						JOptionPane.showMessageDialog(InhaMineSweeper.this, "불러올 게임이 없습니다.", "불러오기 오류", JOptionPane.INFORMATION_MESSAGE );
						err.printStackTrace();
					}
				}
				}
			}
		};
		mb.saveGame.addActionListener(saveLoad);
		mb.loadGame.addActionListener(saveLoad);
	}
	
	/*
	 * 상단 부분에 대한 구현기능
	 * 지뢰 숫자(깃발 숫자), 타이머, 재시작기능이 포함되어있다.
	 * 직렬화가 구현되어 있다.
	 */
	class NorthPart extends JPanel implements Runnable, Serializable{
		private JTextField minesNum;
		private JTextField timer;
		public JButton reset;
		public int time;
		public boolean firstTouch;
		public boolean timePass;
		
		public NorthPart() {
			minesNum = new JTextField(4);
			minesNum.setFont(new Font("Dialog", Font.BOLD, 30));
			reset = new JButton("'_'");
			reset.setBackground(Color.WHITE);
			reset.setOpaque(false);
			minesNum.setForeground(Color.red);
			timer = new JTextField(4);
			timer.setFont(new Font("Dialog", Font.BOLD, 30));
			timer.setForeground(Color.red);
			minesNum.setEditable(false);
			timer.setEditable(false);
			
			reset.addMouseListener(new MouseAdapter() {

				@Override
				public void mouseClicked(MouseEvent e) {
					super.mouseClicked(e);
					reset.setText("'_'");
					setTimerText(0);
					firstTouch = true;
					timePass = false;
					center.makeButton(center.lvl);
					setMinesNumText(center.thisIsMine);
				}
				
			});
			add(minesNum);
			add(reset);
			add(timer);
		}
		public void setMinesNumText(int numOfMines) {
			minesNum.setText("" + numOfMines);
		}
		public void setTimerText(int time) {
			this.time = time;
			timer.setText("" + this.time);
		}
		
		public void run() { // 자바 스레드는 run 메서드를 구현해서 이루어진다. 스레드를 통한 타이머 기능 구현
			while(timePass) {
				try {	
					this.time++;
					Thread.sleep(1000);
				} catch (Exception e) {
				}			
				timer.setText("" + this.time);
			}
		}
	}
	
	/*
	 * 지뢰구현부분에 대한 클래스
	 * 직렬화를 가능하게 해 준다. (게임을 클리어 했을 시 랭킹구현을 해야하므로 여기서도 직렬화를 가능하게 해야한다.)
	 */
	class CenterPart extends JPanel implements Serializable{
		private int[] minesNum;
		JButton[] buttons;
		public int thisIsMine;
		public boolean gameOver;
		public int gameClear;
		public int lvl;
		public boolean gameLoad;
		public int[] mineText;
		
		public CenterPart() {
			north.setTimerText(0);
			north.firstTouch = true;
			north.timePass = false;
			makeButton(1);
			north.setMinesNumText(thisIsMine);
		}
		
		/*
		 * 버튼과 지뢰를 만드는 함수
		 * 난이도에 따라 버튼 수와 지뢰 수를 다르게 한다.
		 * 리스너들을 구현해서 버튼을 클릭했을 때 어떤 기능을 하는 지 구현해준다.
		 */
		public void makeButton(int lvl) {
			this.removeAll();
			thisIsMine = 0;
			gameOver = false;
			gameClear = 0;
			this.lvl = lvl;
			
			int numOfButton;
			int numOfMine;
			if(this.lvl == 1) {
				numOfButton = 100;
				numOfMine = 10;
				mineText = new int[numOfButton];
				this.setLayout(new GridLayout(10, 10));
				buttons = new JButton[numOfButton];
			} else if(this.lvl == 2) {
				numOfButton = 200;
				numOfMine = 40;
				mineText = new int[numOfButton];
				this.setLayout(new GridLayout(20, 10));
				buttons = new JButton[numOfButton];
			} else {
				numOfButton = 600;
				numOfMine = 100;				
				mineText = new int[numOfButton];
				this.setLayout(new GridLayout(30, 20));
				buttons = new JButton[numOfButton];
			}
				if(!gameLoad) {
				minesNum = new int[numOfMine];
				for(int i = 0; i < numOfMine; i++) {
					minesNum[i] = (int)((Math.random() * numOfButton));
					for(int j = 0; j < i; j++) {
						if(minesNum[i] == minesNum[j]) {
							i--;
						}
					}
				}
				}
				Arrays.sort(minesNum); // 랜덤함수 오름차순 정렬
				
				for(int i = 0; i < numOfButton; i++) { // 지뢰배열 생성, 이 곳을 이용해서 추후에 버튼을 누르고 setText할 예정
					mineText[i] = 0;
					for(int j = 0; j < numOfMine; j++) {
						if(i == minesNum[j]) {
							mineText[i] = -100;
						}
						if((lvl == 2 || lvl == 1) && (i + 1) == minesNum[j] && ((i+1) % 10) != 0) {
							mineText[i]++;
						}
						if((lvl == 2 || lvl == 1) && (i - 1) == minesNum[j] && (i % 10) != 0) {
							mineText[i]++;
						}
						if((lvl == 2 || lvl == 1) && (i - 9) == minesNum[j] && ((i+1) % 10) != 0) {
							mineText[i]++;
						}
						if((lvl == 2 || lvl == 1) && (i - 10) == minesNum[j]) {
							mineText[i]++;
						}
						if((lvl == 2 || lvl == 1) && (i - 11) == minesNum[j] && (i % 10) != 0) {
							mineText[i]++;
						}						
						if((lvl == 2 || lvl == 1) && (i + 9) == minesNum[j] && (i % 10) != 0) {
							mineText[i]++;
						}
						if((lvl == 2 || lvl == 1) && (i + 10) == minesNum[j]) {
							mineText[i]++;
						}
						if((lvl == 2 || lvl == 1) && (i + 11) == minesNum[j] && ((i+1) % 10) != 0) {
							mineText[i]++;
						}
						
						if((lvl == 3) && (i + 1) == minesNum[j] && ((i+1) % 20) != 0) {
							mineText[i]++;
						}
						if((lvl == 3) && (i - 1) == minesNum[j] && (i % 20) != 0) {
							mineText[i]++;
						}
						if((lvl == 3) && (i - 19) == minesNum[j] && ((i+1) % 20) != 0) {
							mineText[i]++;
						}
						if((lvl == 3) && (i - 20) == minesNum[j]) {
							mineText[i]++;
						}
						if((lvl == 3) && (i - 21) == minesNum[j] && (i % 20) != 0) {
							mineText[i]++;
						}						
						if((lvl ==3) && (i + 19) == minesNum[j] && (i % 20) != 0) {
							mineText[i]++;
						}
						if((lvl == 3) && (i + 20) == minesNum[j]) {
							mineText[i]++;
						}
						if((lvl == 3) && (i + 21) == minesNum[j] && ((i+1) % 20) != 0) {
							mineText[i]++;
						}
					}
				}
				
				for(int i = 0; i < numOfButton; i++) { // 지뢰인 버튼과 아닌 버튼을 따로 리스너를 정해줌.	
					final int num = i;
					if(thisIsMine < numOfMine && i == minesNum[thisIsMine]) { // 지뢰버튼 
						buttons[i] = new JButton(""); 
						thisIsMine++;
						buttons[i].addMouseListener(new MouseAdapter() { // 지뢰버튼들에 대한 마우스리스너 추가
							@Override
							public void mouseClicked(MouseEvent e) {
								JButton button = (JButton)e.getSource();
								if(e.getButton() == MouseEvent.BUTTON1 && button.isEnabled()) {
								super.mouseClicked(e);
								north.timePass = false;
								north.reset.setText("x_x");
								JOptionPane.showMessageDialog(InhaMineSweeper.this, "지뢰를 밟았습니다!\n경과한 시간 : " + north.time + "초 \n난이도 : " + ((lvl == 1) ? "초급" : (lvl == 2) ? "중급" : "고급")
										+ "\n찾은 빈칸 수 : " + center.gameClear+ "\n스코어 : " +  (int)((Math.sqrt(lvl*lvl*lvl*lvl*lvl) * center.gameClear * 100) / (north.time+1)), 
										"GAME OVER", JOptionPane.INFORMATION_MESSAGE );
								gameOver = true;
								for(int i = 0; i < numOfButton; i++) {
									for(int j = 0; j < numOfMine; j++) {
										if( (i == minesNum[j] && buttons[i].isEnabled() ) ) { // 지뢰인 곳 표시
											buttons[i].setOpaque(true);
											buttons[i].setBackground(Color.RED);
											buttons[i].setText("*");
											break;
										} else if (( i == minesNum[j] && !buttons[i].isEnabled() && !buttons[i].isSelected() )) { // 지뢰를 찾은곳 지뢰가 맞다고 표시
											buttons[i].setOpaque(true);
											buttons[i].setBackground(Color.RED);
											buttons[i].setText("O");
											break;
										} else if(i != minesNum[j] && !buttons[i].isEnabled() && !buttons[i].isSelected()) { // 지뢰가 아닌데 깃발이 있었다면 아니였다고 표시
											buttons[i].setOpaque(true);
											buttons[i].setBackground(Color.ORANGE);
											buttons[i].setText("X");
										}
									}
								}
								for(int i = 0; i < numOfButton; i++) { // 지뢰를 밟고 나머지 버튼들 못누르게 하기
									buttons[i].setEnabled(false);
								}
							}
							}
						});
						} 
					else { // 지뢰버튼이 아니라면
						buttons[i] = new JButton("");
						buttons[i].addMouseListener(new MouseAdapter() { // 지뢰버튼이 아닌 곳에 리스너추가
							@Override
							public void mouseClicked(MouseEvent e) {
								JButton button = (JButton)e.getSource();
								super.mouseClicked(e);
								
								if(e.getButton() == MouseEvent.BUTTON1 && button.isEnabled() && !gameOver) { // 마우스 왼쪽버튼을 눌렀을 때
								checkBlank(buttons, num);
								}
								if( ((lvl == 1 && gameClear == 90) || (lvl == 2 && gameClear == 160) || (lvl == 3 && gameClear == 500)) && thisIsMine >= 0 && button.isSelected()) { // 게임 클리어 조건
									north.reset.setText("^_^");
									north.timePass = false;
									String level = ((lvl == 1) ? "초급" : (lvl == 2) ? "중급" : "고급");
									int score = (int)((Math.sqrt(lvl*lvl*lvl*lvl*lvl) * center.gameClear * 100) / (north.time+1));
									for(int i = 0; i < numOfButton; i++) {
										for(int j = 0; j < numOfMine; j++) {
											if( (i == minesNum[j] && buttons[i].isEnabled() ) ) { // 지뢰인 곳 표시
												buttons[i].setOpaque(true);
												buttons[i].setBackground(Color.BLUE);
												break;
											}
										}
									}
									for(int i = 0; i < numOfButton; i++) { // 나머지 버튼들 못누르게 하기
										buttons[i].setEnabled(false);
									}
									JOptionPane.showMessageDialog(InhaMineSweeper.this, "게임을 클리어했습니다!\n경과한 시간 : " + north.time + "초 \n난이도 : " 
									+ level + "\n스코어 : " + score, 
											"GAME CLEAR", JOptionPane.INFORMATION_MESSAGE );
									rank.add(new Ranking(level, north.time, score));
									if(rank.size() >= 10 && rank.get(9).clearScore >= rank.get(8).clearScore) {
										rank.remove(8);
									} else if(rank.size() >= 10 && rank.get(9).clearScore < rank.get(8).clearScore) {
										rank.remove(9);
									}
									Collections.sort(rank);
									try (DataOutputStream dosr = new DataOutputStream(new FileOutputStream("C:\\Download\\InhaMineSweeperRank.dat")) ) {
										dosr.write(rank.size());
										for(int i = 0; i < rank.size(); i++) {
											dosr.writeUTF(rank.get(i).level);
											dosr.write(rank.get(i).clearTime);
											dosr.write(rank.get(i).clearScore);
										}
										dosr.flush();
										dosr.close();
									} catch (IOException err) {
									}
								}
							}
						});
						}
					buttons[i].setBackground(Color.white);
					buttons[i].setOpaque(false);
					this.add(buttons[i]);
			}
				
				for(int i = 0; i < numOfButton; i++) { // 모든 JButton에 해당하는 마우스리스너 : 1. 마우스 우클릭 깃발저장(파란색으로 만듦), 2. 타이머 시작
					buttons[i].addMouseListener(new MouseAdapter() {
						@Override
						public void mouseClicked(MouseEvent e) {
							JButton button = (JButton)e.getSource();
							super.mouseClicked(e);
							if(e.getButton() == MouseEvent.BUTTON3 && button.isEnabled() && !gameOver && !button.isSelected()) {
								button.setOpaque(true);
								button.setBackground(Color.BLUE);
								button.setEnabled(false);
								thisIsMine--;
								north.setMinesNumText(thisIsMine);
							} else if (e.getButton() == MouseEvent.BUTTON3 && !button.isEnabled() && !gameOver && !button.isSelected()) {
								button.setOpaque(false);
								button.setEnabled(true);
								thisIsMine++;
								north.setMinesNumText(thisIsMine);
							}
							if ( (e.getButton() == MouseEvent.BUTTON1 || e.getButton() == MouseEvent.BUTTON3 ) && north.firstTouch && !gameOver) {
								north.timePass = true;
								new Thread(north).start();
								north.firstTouch = false;
							}
						}
					});
				}
			revalidate();
		}
		
		public void checkBlank(JButton[] j, int idx) { // 재귀함수로 구현한 지뢰가 아닐 경우 여러칸이 열리는 기능
			if(idx < 0 || idx >= buttons.length) { return; }
			if(!j[idx].isEnabled()) { return; }
			j[idx].setOpaque(true);
			j[idx].setSelected(true);
			j[idx].setEnabled(false);
			gameClear++;
			j[idx].setBackground(Color.LIGHT_GRAY);
			j[idx].setText("" + mineText[idx]);
			if (mineText[idx] == 0 && (lvl == 1 || lvl == 2) && ((idx + 1) % 10) == 0){
				checkBlank(j, idx-11);
				checkBlank(j, idx-10);
				checkBlank(j, idx-1);
				checkBlank(j, idx+9);
				checkBlank(j, idx+10);
			} else if (mineText[idx] == 0 && (lvl == 1 || lvl == 2) && (idx  % 10) == 0) {
				checkBlank(j, idx+11);
				checkBlank(j, idx+10);
				checkBlank(j, idx+1);
				checkBlank(j, idx-9);
				checkBlank(j, idx-10);
			} else if (mineText[idx] == 0 && (lvl == 1 || lvl == 2)) {
				checkBlank(j, idx+11);
				checkBlank(j, idx+10);
				checkBlank(j, idx+1);
				checkBlank(j, idx-9);
				checkBlank(j, idx-11);
				checkBlank(j, idx-10);
				checkBlank(j, idx-1);
				checkBlank(j, idx+9);
			}
			if (mineText[idx] == 0 && lvl == 3 && ((idx + 1) % 20) == 0){
				checkBlank(j, idx-21);
				checkBlank(j, idx-20);
				checkBlank(j, idx-1);
				checkBlank(j, idx+19);
				checkBlank(j, idx+20);
			} else if (mineText[idx] == 0 && lvl == 3 && (idx  % 20) == 0) {
				checkBlank(j, idx+21);
				checkBlank(j, idx+20);
				checkBlank(j, idx+1);
				checkBlank(j, idx-19);
				checkBlank(j, idx-20);
			} else if (mineText[idx] == 0 && lvl == 3) {
				checkBlank(j, idx+21);
				checkBlank(j, idx+20);
				checkBlank(j, idx+1);
				checkBlank(j, idx-19);
				checkBlank(j, idx-21);
				checkBlank(j, idx-20);
				checkBlank(j, idx-1);
				checkBlank(j, idx+19);
			}
		}
	}
	
	/*
	 * 메뉴바 클래스
	 */
	class MineSweeperMenuBar extends JMenuBar{
		JMenu menu1;
		JMenu menu2;
		JMenu menu3;
		JMenu newGame;
		JMenuItem exitGame;
		JMenuItem loadGame;
		JMenuItem saveGame;
		JMenuItem hard;
		JMenuItem normal;
		JMenuItem easy;
		JMenuItem helper;
		JMenuItem ranking;
		public MineSweeperMenuBar() {
			menu1 = new JMenu("게임");
			menu2 = new JMenu("파일");
			menu3 = new JMenu("도구");
			newGame = new JMenu("새 게임");
			exitGame = new JMenuItem("종료하기");
			loadGame = new JMenuItem("불러오기");
			saveGame = new JMenuItem("저장");
			hard = new JMenuItem("고급 (30x20)");
			normal = new JMenuItem("중급 (20x10)");
			easy = new JMenuItem("초급 (10x10)");
			helper = new JMenuItem("도움말");
			ranking = new JMenuItem("랭킹");
			menu1.add(newGame);
			newGame.add(easy);
			newGame.add(normal);
			newGame.add(hard);
			menu1.addSeparator();
			menu1.add(exitGame);
			menu2.add(saveGame);
			menu2.addSeparator();
			menu2.add(loadGame);
			menu3.add(helper);
			menu3.add(ranking);
			this.add(menu1);
			this.add(menu2);
			this.add(menu3);
		}
	}
	
	/*
	 * 랭킹 구현 클래스,
	 * Serializable을 상속받아 직렬화를 구현한다.
	 * compareTo 메서드를 오버라이드해서 대소비교를 clearScore가 기준이 되게한다.
	 */
	class Ranking implements Comparable<Ranking>, Serializable {
		String level;
		int clearScore;
		int clearTime;
		
		public Ranking(String level,int clearTime, int clearScore) {
			this.level = level;
			this.clearScore = clearScore;
			this.clearTime = clearTime;
		}
		
		@Override
		public int compareTo(Ranking rank) {
			if(clearScore > rank.clearScore) { return -1; }
			else if(clearScore == rank.clearScore) { return 0; }
			else { return 1; }
		}
		
	}
	
	public static void main(String[] args) {
		new InhaMineSweeper();
	}

}
