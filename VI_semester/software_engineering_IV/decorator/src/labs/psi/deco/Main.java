package labs.psi.deco;

public class Main {
	public static void main(String[] args){
		Message m = createMessage("Buy some cookies.", "Tumas", true, true);
		System.out.println(m.preview());
		
		EncryptedMessage em = (EncryptedMessage) MessageDecorator.getRole((MessageDecorator)m, "EncryptedMessage");
		if (em != null){
			System.out.println("Decrypted: " + (em.decrypt()));
		}
		
		Message m2 = createMessage("And some milk too", "Tumas", true, true);
		System.out.println(m2.preview());
		
		System.out.println("Removing date:");
		System.out.println(MessageDecorator.removeRole((MessageDecorator)m2, "EncryptedMessage").preview());
	}
	
	public static Message createMessage(String message, String author, boolean dated, boolean encrypted){
		Message m = new SimpleMessage(message);
	
		if (encrypted) 		 m = new EncryptedMessage(m);
		if (author != null) m = new SignedMessage(m, author);
		if (dated) 			 m = new DatedMessage(m);
		return m;
	}
}