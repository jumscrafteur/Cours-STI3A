import stacks.Stack;

public class Browser {
  private Stack prev, next;
  private String current = "https://fr.wikipedia.org/wiki/Sp%C3%A9cial:Page_au_hasard";

  Browser(int size) {
    this.prev = new Stack(size);
    this.next = new Stack(size);
  }

  public String getCurrentAdress() {
    return this.current;
  }

  public void nextAdress() {
    if (next.isEmpty())
      return;

    next.push(current);
    current = prev.pop();
  }

  public void previousAdress() {
    if (prev.isEmpty())
      return;

    prev.push(current);
    current = next.pop();
  }

  public void newAdress(String newSite) {
    prev.push(current);
    current = newSite;
    next.flush();
  }

}
