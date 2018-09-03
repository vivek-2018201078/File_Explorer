Terminal Based File Explorer

A file exploer which works in 2 modes
1. normal mode
2.command mode
Application starts in Normal mode
Application ends with ctrl-c or q
Root of the application is where apllication is started
file explorer is restricted to root and its child directory and no other folders/files outside it
Last line of the application is status bar which shows which mode you are working in (NORMAL MODE written specifies normal moe otherwise in command mode status bar accepts commands)

Normal mode
	1.Normal mode shows listing of directory with current directory path at end displayed (1 entry per line)
	2.Listing shows
		a) File name
		b) File size (size is shown in format of ls -lh)
		c) Ownership (User & Group) & Permissions
		d) Last modified
	3.you can do vertical scrolling once your application has started provided you do not change terminal size after application has 		  started. Restriction on height of terminal is 4
	4.shows entries . and .. where when pressed .. goes 1 directory up
	5. arrow keys up and down move cursor up and down and cursor does not move beyond number of entries in directory
	6. You can open directory/file by pressing enter at corresponding cursor location. (files which has no default application to open shows 	    error and may show weird result and may break cursor. press backspace to go 1 directory up to reset)	
	7. you can traverse through directories with left and right arrow keys to go to previously visited directory or forward uptill you have 	   traversed the directories.
	8. backspace goes 1 directory up pressing h goes to root directory.

Command Mode
	1. Enter command mode by pressing : and exit by pressing esc
	2. you can enter different commands which are listed below
	3. if command operation is successful command executed appears on status bar and application waits for next command
	4. if command operationis unsuccessful wrong command or path type again is shown.
	5. Commands that can be executed and its assumptions are given below
		A) Copy ‘:copy <source_file(s)> <destination_directory>’
			multiple files or directories can be copied to destination directory
			assumptions:
				a) file or folder to be copied should be in current directory
				b) destination path is relative to root
				c) all file/folder name and directory name exits already
		B) Move ‘:move <source_file(s)> <destination_directory>’ 
			move multipe files or directories to destination directory
			assumptions:
				a) file or folder to be copied should be in current directory
				b) destination path is relative to root
				c) all file/folder name and directory name exits already
		C) Rename ‘:rename <old_filename> <new_filename>’
			renames from old to new
			assumptions:
				a) files or folders to be renamed are in current directory or you have to give relative path from current 					   directory to both old and new
		D) Create file ‘:create_file <file_name> <destination_path>’
		   Create directory ‘:create_dir <dir_name> <destination_path>’
			assumptions:
				a)destination path is relative to root
				b) all file/folder name and directory name exits already

		E) Snapshot ':snapshot <directory name> <output-file>'
			creates a snapshot dump in root with given file name of directory name
			assumptions:
				a)if / is passed as directory argument, snapshot of root is dumped
				b)otherwise snapshot will be of directory mentioned whch is in current directory
				c) all file/folder name and directory name exits already
	6. ESC goes back to normal mode

Basic assumption
1. terminal size is minimum 80 * 4
2. Verical scrolling is possible for any terminal height except < 4
3. wrap around is not possible therefor terminal width should be minimum 80
4. Backspace in command work doesnt work like normal backspace. You have to write command again if you mistype after pressing backspace

			 
			


		
