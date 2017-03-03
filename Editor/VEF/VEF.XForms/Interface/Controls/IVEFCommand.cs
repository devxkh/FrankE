using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Input;

namespace VEF.Interfaces.Controls
{
	/// <summary>
	/// An interface to provide the Command pattern implementation. Command objects can be used
	/// in conjunction with other classes such as an undo/redo stack.
	/// </summary>
    public interface IVEFCommand : ICommand, IDisposable
	{
		/// <summary>
		/// Determine if this command supports undo
		/// </summary>
		/// <returns>true if this command can be undone, false otherwise</returns>
		bool CanUndo();

		
		/// <summary>
		/// Determine if this command supports redo
		/// </summary>
		/// <returns>true if this command be can redone, false otherwise</returns>
		bool CanRedo();

		
		/// <summary>
		/// Determine if this command can be executed. Executed commands are those that will
		/// be run automatically when added to the undo/redo stack. Batch style commands should
		/// not be executed since they will have already performed their operations.
		/// </summary>
		/// <returns>true if the command should be executed, false otherwise</returns>
		//bool CanExecute();


		/// <summary>
		/// Undoes the operations that this command performed.
		/// </summary>
		void Undo();


		/// <summary>
		/// Redoes the operations that this command performed.
		/// </summary>
		void Redo();


		/// <summary>
		/// Executes this command. Commands that are "pre-rolled" and have already performed
		/// their operations should never require this method. Batch style commands are an
		/// example of a command that should not require execution but can be undone/redone.
		/// </summary>
	//	void Execute();


		/// <summary>
		/// A short descriptive message about this command.
		/// </summary>
		/// <returns></returns>
		String ShortMessage();

	}
}
